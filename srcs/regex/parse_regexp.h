#ifndef LIBFT_PARSE_REGEXP_H
#define LIBFT_PARSE_REGEXP_H
#include "internal_ft_regex.h"

typedef int (*reg_handler)(AST *tree, const char *restrict pattern);

int	dot_handler( AST *tree, const char *restrict pattern);
int	regular_handler( AST *tree, const char *restrict pattern);
int	asterisk_handler( AST *tree, const char *restrict pattern);
int question_mark_handler(AST *tree, const char *restrict pattern);
int plus_handler(AST *tree, const char *restrict pattern);
int	open_bracket_handler( AST *tree, const char *restrict pattern);
int	close_bracket_handler( AST *tree, const char *restrict pattern);
int	end_handler( AST *tree, const char *restrict pattern);
int	begin_handler( AST *tree, const char *restrict pattern);
int	slash_handler( AST *tree, const char *restrict pattern);
int	equivalence_class_handler( AST *tree, const char *restrict pattern);
int	collating_element_handler( AST *tree, const char *restrict pattern);
int	char_class_handler( AST *tree, const char *restrict pattern);
int range_repeat_handler(AST *tree, const char *restrict pattern);
int open_subexpr_handler( AST *tree, const char *restrict pattern);
int close_subexpr_handler( AST *tree, const char *restrict pattern);
int escaped_regular_handler(AST *tree, const char *restrict pattern);
int char_range_handler(AST *tree, const char *restrict pattern);
int	pipe_handler(AST *tree, const char *restrict pattern);


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

#endif //LIBFT_PARSE_REGEXP_H
