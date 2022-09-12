#ifndef LIBFT_INTERNAL_FT_REGEX_H
#define LIBFT_INTERNAL_FT_REGEX_H
#include "ft_regex.h"
#include "wctype.h"
# define STATIC_ARRAY_SIZE(array) (sizeof (array) / sizeof (*array))

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
		wchar_t _char;
		struct {
			struct reg_node *tok;
			ssize_t	min;
			ssize_t	max;
		} repeated;
		container	sub;
		wchar_t		equivalence_class;
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

typedef int (*reg_handler)(ft_regex_t *restrict preg, const char *restrict pattern);

int	dot_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	regular_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	asterisk_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int question_mark_handler(ft_regex_t *restrict preg, const char *restrict pattern);
int plus_handler(ft_regex_t *restrict preg, const char *restrict pattern);
int	open_bracket_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	close_bracket_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	end_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	begin_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	slash_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	equivalence_class_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	collating_element_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int	char_class_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int range_repeat_handler(ft_regex_t *restrict preg, const char *restrict pattern);
int open_subexpr_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int close_subexpr_handler( ft_regex_t *restrict preg, const char *restrict pattern);
int escaped_regular_handler(ft_regex_t *restrict preg, const char *restrict pattern);
int char_range_handler(ft_regex_t *restrict preg, const char *restrict pattern);
int	pipe_handler(ft_regex_t *restrict preg, const char *restrict pattern);


// all condition in mask must be verified and all condition in not_mask must NOT be verified
const static struct {char *str; reg_handler handler; int mask; int not_mask;} handler_map[] = {
	{"[=", &equivalence_class_handler, REG_IN_BRACKET			, 0},
	{"[.", &collating_element_handler, REG_IN_BRACKET			, 0},
	{"[:", &char_class_handler,        REG_IN_BRACKET			, 0},
	{"\\{", &range_repeat_handler,     0						, REG_ERE | REG_ESCAPED | REG_IN_BRACKET | REG_FIRST},
	{"\\)", &close_subexpr_handler,    0						, REG_ERE | REG_ESCAPED | REG_IN_BRACKET},
	{"\\(", &open_subexpr_handler,     0						, REG_ERE | REG_ESCAPED | REG_IN_BRACKET},
	{"|", &pipe_handler,   	           REG_ERE					, REG_ESCAPED | REG_IN_BRACKET | REG_FIRST},
	{"{", &range_repeat_handler,       REG_ERE					, REG_ESCAPED | REG_IN_BRACKET | REG_FIRST},
	{"*", &asterisk_handler,           0						, REG_ESCAPED | REG_IN_BRACKET | REG_FIRST},
	{"+", &plus_handler,          	   REG_ERE					, REG_ESCAPED | REG_IN_BRACKET | REG_FIRST},
	{"?", &question_mark_handler,      REG_ERE					, REG_ESCAPED | REG_IN_BRACKET | REG_FIRST},
	{".", &dot_handler,                0						, REG_ESCAPED | REG_IN_BRACKET},
	{"(", &open_subexpr_handler,       REG_ERE					, REG_ESCAPED | REG_IN_BRACKET},
	{")", &close_subexpr_handler,      REG_ERE					, REG_ESCAPED | REG_IN_BRACKET},
	{"[", &open_bracket_handler,       0						, REG_ESCAPED | REG_IN_BRACKET},
	{"]", &close_bracket_handler,      REG_IN_BRACKET			, REG_FIRST},
	{"^", &begin_handler,              0						, REG_IN_BRACKET | REG_ESCAPED},
	{"$", &end_handler,                0						, REG_IN_BRACKET | REG_ESCAPED},
	{"\\", &slash_handler,             0						, REG_IN_BRACKET | REG_ESCAPED},
	{NULL, &escaped_regular_handler,   REG_ESCAPED				, 0},
	{NULL, &regular_handler, 0, 0},
};

#endif
