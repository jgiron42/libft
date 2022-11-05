#ifndef LIBFT_INTERNAL_FT_REGEX_H
#define LIBFT_INTERNAL_FT_REGEX_H
#include "ft_regex.h"
#include "wctype.h"
#include <malloc.h>
#define FT_RE_DUP_INF (FT_RE_DUP_MAX + 1)
#define FT_RE_BEGIN	256
#define FT_RE_END	257
typedef enum {
	REG_FIRST = 1,
	REG_ESCAPED = 4,
	REG_IN_BRACKET = 8,
//	REG_FIRST_IN_BRACKET = 16,
	REG_ERE = 32,
//	REG_REPEATABLE = 16,
}	reg_context;

typedef enum {
	REG_DOT,
	REG_CHAR,
	REG_REPEATED,
	REG_KLEENE,
	REG_BEGIN,
	REG_END,
	REG_BRACKET,
	REG_SUB,
	REG_EQUIVALENCE,
	REG_COLLATING_ELEMENT,
	REG_CLASS,
	REG_RANGE,
	REG_BACK_REF,
	REG_PIPE,
}	reg_token_type;

typedef struct reg_node {
	reg_token_type	type;
	bool			invert;
	char			sub_expr_dependency[9]; // on which sub expr depends this node
	size_t			sub_index;
	ssize_t 		current;
	union {
		unsigned char _char;
		struct {
			struct reg_node *tok;
			ssize_t	min;
			ssize_t	max;
		} repeated;
		struct reg_node *kleene;
		container	sub; // container of pointer to reg_node
		char		equivalence_class;
		wctype_t 	char_class;
		char		*collating_element;
		struct {
			unsigned char begin;
			unsigned char end;
		}			range;
		int			back_ref;
	};
	struct reg_node *parent;
}		reg_node;

typedef struct
{
	reg_context context;
	reg_node	*current;
	size_t		index;
}		reg_state;

typedef struct
{
	size_t			begin;
	size_t			end;
	ft_regmatch_t	*pmatch;
	size_t			nmatch;
	int				eflags;
}		regexec_t;

typedef struct FA_state {
	int			id; // if -1 then the state is a subset
	container	*subset; // used in powerset construction
	bool		accept; // true if the state is an accept state
	size_t		link_to; // the number of link to this node
	union{
		struct { // when the machine is non-deterministic their can be several transition for each symbol, that's why we store them in sets
			container	*ascii[256 + 2]; // ascii + two for begin ('^') and end ('$')
			container	*epsilon; // epsilon transitions
		}		nd; // non-deterministic
		struct { // when the machine is deterministic we store directly the only transition for each entry and there is no more epsilons
			struct FA_state *ascii[256 + 2]; // ascii + two for begin ('^') and end ('$')
		}		d; // deterministic
	};
}				FA_state;

typedef struct {
	struct {
		int				context;
		struct reg_node	*current;
		size_t			index;
	}					state;
	reg_node	*root;
	container	sub_vec; // contain link to all subexpressions
	container	node_vec;
	int			cflags;
}	AST;

typedef struct finite_automaton{
	FA_state	*begin;
	FA_state	*end;
	bool		deterministic;
	container	states;
}			finite_automaton;

int			parse_regexp(ft_regex_t *restrict r, AST *tree, const char *restrict pattern, int cflags);
status		get_raw_graph(int cflags, AST *tree, finite_automaton *raw_graph);
void		remove_unused_states(finite_automaton *raw_graph);
void		destroy_transitions(FA_state state);
void		destroy_automaton(finite_automaton *automaton);
FA_state	*get_new_state(container *raw_graph);
status		create_link(container **src, FA_state *dst);
status		make_deterministic(finite_automaton *automaton);
void		print_graph(finite_automaton *automaton);
status		remove_all_epsilon(finite_automaton *raw_graph);
void		destroy_tree(AST *tree);
void		get_graphml(finite_automaton *automaton, char *name);
int			state_compare(type_metadata prop, void *l, void *r);
status		powerset_construction(finite_automaton *automaton);

#endif
