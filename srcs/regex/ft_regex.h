#ifndef LIBFT_FT_REGEX_H
#define LIBFT_FT_REGEX_H
#include <sys/types.h>
#include "libft.h"
#include "../containers/containers.h"
#define FT_RE_DUP_MAX RE_DUP_MAX
typedef size_t ft_regoff_t;

typedef struct {
	size_t				re_nsub; // Number of parenthesized subexpressions
	int					cflags;
	bool				bol; // must match beginning of string
	bool				eol; // must match end of string
	struct finite_automaton	*graph;
}		ft_regex_t;

typedef struct {
	ft_regoff_t			rm_so; // Byte offset from start of string to start of substring
	ft_regoff_t			rm_eo; // Byte offset from start of string of the first character after the end of substring.
	ft_regoff_t			tmp_so;
	ft_regoff_t			tmp_eo;
}		ft_regmatch_t;
enum {
	FT_REG_NOMATCH = 1,	// regexec() failed to match.
	FT_REG_BADPAT,		// Invalid regular expression.
	FT_REG_ECOLLATE,	// Invalid collating element referenced.
	FT_REG_ECTYPE,		// Invalid character class type referenced.
	FT_REG_EESCAPE,		// Trailing <backslash> character in pattern.
	FT_REG_ESUBREG,		// Number in \digit invalid or in error.
	FT_REG_EBRACK,		// "[]" imbalance.
	FT_REG_EPAREN,		// "\(\)" or "()" imbalance.
	FT_REG_EBRACE,		// "\{\}" imbalance.
	FT_REG_BADBR,		// Content of "\{\}" invalid: not a number, number too large, more than two numbers, first larger than second.
	FT_REG_ERANGE,		// Invalid endpoint in range expression.
	FT_REG_ESPACE,		// Out of memory.
	FT_REG_BADRPT,		//	'?', '*', or '+' not preceded by valid regular expression.
};

enum {
	FT_REG_EXTENDED = 1, // Use Extended Regular Expressions.
	FT_REG_ICASE = 2, // Ignore case in match (see XBD Regular Expressions).
	FT_REG_NOSUB = 4, // Report only success/fail in regexec().
	FT_REG_NEWLINE = 8, // Change the handling of <newline> characters, as described in the text.
	FT_REG_NOTBOL = 16, // Change the handling of <newline> characters, as described in the text.
	FT_REG_NOTEOL = 32, // Change the handling of <newline> characters, as described in the text.
};

int    ft_regcomp(ft_regex_t *restrict, const char *restrict, int);
size_t ft_regerror(int, const ft_regex_t *restrict, char *restrict, size_t);
int    ft_regexec(const ft_regex_t *restrict, const char *restrict, size_t, ft_regmatch_t [restrict], int);
void   ft_regfree(ft_regex_t *);

#endif
