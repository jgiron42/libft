#include "internal_ft_regex.h"

reg_node *new_node(container *vec, reg_node  node)
{
	if (ft_vector_push_back(vec, &node) != OK)
		return NULL;
	return ft_vector_back(vec);
}

int asterisk_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_REPEATED, .parent = preg->state.current, .repeated = {
			.tok = ft_vector_back(&preg->state.current->sub), // the repeated element is the last from the parent
			.min = 0,
			.max = FT_RE_DUP_MAX
	}});
	ft_vector_pop_back(&preg->state.current->sub); // remove the element from the parent
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tmp->repeated.tok->parent = tmp;
	preg->state.index++;
	return 0;
}

int range_repeat_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	preg->state.index++;
	if (!strstr(pattern + preg->state.index, "\\}"))
		return FT_REG_EBRACE;
	char *end;
	long int min = ft_strtol(pattern + preg->state.index, &end, 10);
	long int max = min;
	if (*end == ',')
	{
		if (ft_isdigit(end[1]))
			max = ft_strtol(end + 1, &end, 10);
		else
		{
			max = FT_RE_DUP_MAX;
			end++;
		}
	}
	if (min < 0 || min > FT_RE_DUP_MAX || max < 0 || max > FT_RE_DUP_MAX || ft_strncmp(end, "\\}", 2))
		return FT_REG_BADBR;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_REPEATED, .parent = preg->state.current, .repeated = {
			.tok = ft_vector_back(&preg->state.current->sub), // the repeated element is the last from the parent
			.min = min,
			.max = max
	}});

	ft_vector_pop_back(&preg->state.current->sub); // remove the element from the parent
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.index = end - pattern;
	return 0;
}

int open_bracket_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_BRACKET, .parent = preg->state.current});
	if (ft_vector(ATOMIC_TYPE, &tmp->sub) != OK)
		return FT_REG_ESPACE;
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.current = tmp;
	preg->state.context |= REG_IN_BRACKET | REG_FIRST_IN_BRACKET;
	preg->state.index++;
	return 0;
}

int close_bracket_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	preg->state.current = preg->state.current->parent;
	preg->state.context &= ~REG_IN_BRACKET;
	preg->state.index++;
	return 0;
}

int open_subexpr_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_SUB, .parent = preg->state.current});
	if (ft_vector(ATOMIC_TYPE, &tmp->sub) != OK)
		return FT_REG_ESPACE;
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	if (ft_vector_push_back(&preg->sub_vec, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.current = tmp;
	preg->state.index += 2;
	return 0;
}

int close_subexpr_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	if (!preg->state.current->parent)
		return FT_REG_EPAREN;
	preg->state.current = preg->state.current->parent;
	preg->state.index += 2;
	return 0;
}

int back_ref_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	size_t n = pattern[preg->state.index] - '0';
	// check if the referenced node exist
	if (n > preg->sub_vec.size)
		return FT_REG_ESUBREG;
	// check if the referenced sub expression is well closed:
	reg_node *ref = ft_vector_at(&preg->sub_vec,n);
	for (reg_node *tmp = preg->state.current; tmp; tmp = tmp->parent)
		if (ref == tmp)
			return FT_REG_ESUBREG;

	for (reg_node *node = preg->state.current; node; node = node->parent) // now all the ancestors of the node depends on this subexpression
		node->sub_expr_dependency[n] = true;

	for (reg_node *node = ref; node; node = node->parent) // and the ancestor of the refered node depends on this one
		node->sub_expr_dependency[preg->sub_vec.size - 1] = true;

	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_BACK_REF, .back_ref = (int)n, .parent = preg->state.current});
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.index+=2;
	preg->state.context &= ~REG_ESCAPED;
	return 0;
}

int regular_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_CHAR, ._char = pattern[preg->state.index], .parent = preg->state.current}); // TODO: wide characters
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.context &= ~REG_ESCAPED;
	preg->state.index++;
	return 0;
}

int escaped_regular_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	if (ft_isdigit(pattern[preg->state.index]))
		return back_ref_handler(preg, pattern);
	else
		return regular_handler(preg, pattern);
}

int dot_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_DOT, .parent = preg->state.current});
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.index++;
	return 0;
}

int begin_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_BEGIN, .parent = preg->state.current});
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.index++;
	return 0;
}

int end_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_END, .parent = preg->state.current});
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.index++;
	return 0;
}

int slash_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	preg->state.context |= REG_ESCAPED;
	preg->state.index++;
	return 0;
}

int	get_val(const char *s, char *end_str, char **dst)
{
	char * end = ft_strstr(s, end_str); // TODO: replace by wcsstr()
	if (!end)
		return FT_REG_EBRACK; // TODO: check if this is the right code
	char *tmp = ft_strndup(s, end - s);
	if (!tmp)
		return FT_REG_ESPACE;
	*dst = tmp;
	return 0;
}

int char_class_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	preg->state.index += 2;
	char *tmps;
	int ret = get_val(pattern + preg->state.index, ":]", &tmps);
	if (ret)
		return ret;
	wctype_t type = wctype(tmps);
	free(tmps);
	if (!type)
		return FT_REG_ECTYPE;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_CLASS, .parent = preg->state.current, .char_class = type});
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.index = ft_strstr(pattern + preg->state.index, ":]") + 2 - pattern;
	return 0;
}

int collating_element_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	preg->state.index += 2;
	char *s;
	int ret = get_val(pattern + preg->state.index, ".]", &s);
	if (ret)
		return ret;
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_COLLATING_ELEMENT, .parent = preg->state.current, .collating_element = s});
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
	{
		free(s);
		return FT_REG_ESPACE;
	}
	preg->state.index = ft_strstr(pattern + preg->state.index, ".]") + 2 - pattern;
	return 0;
}

int equivalence_class_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	preg->state.index += 2;
	char *s;
	int ret = get_val(pattern + preg->state.index, "=]", &s);
	if (ret)
		return ret;
	if (ft_strlen(s) != 1) // TODO: replace by wcslen
		return FT_REG_ECOLLATE;
	free(s);
	reg_node *tmp = new_node(&preg->node_vec, (reg_node){.type = REG_EQUIVALENCE, .equivalence_class = pattern[preg->state.index], .parent = preg->state.current}); // TODO: wide characters
	if (ft_vector_push_back(&preg->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	preg->state.index = ft_strstr(pattern + preg->state.index, "=]") + 2 - pattern;
	return 0;
}

int invert_bracket_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	(void)pattern;
	preg->state.current->invert = true;
	preg->state.index++;
	return 0;
}

int char_range_handler(ft_regex_t *restrict preg, const char *restrict pattern)
{
	reg_node *last = ft_vector_back(&preg->state.current->sub);
	if (last->type != REG_CHAR || !ft_isascii(last->_char) || !pattern[preg->state.index + 1] || !ft_isascii(pattern[preg->state.index + 1]))
		return regular_handler(preg, pattern);
	last->type = REG_RANGE;
	if (last->_char < pattern[preg->state.index + 1]) {
		last->range.begin = last->_char;
		last->range.end = pattern[preg->state.index + 1];
	}
	else {
		last->range.begin = pattern[preg->state.index + 1];
		last->range.end = last->_char;
	}
	preg->state.index += 2;
	return 0;
}



int    ft_regcomp(ft_regex_t *restrict preg, const char *restrict pattern, int cflags)
{
	preg->state.context = REG_FIRST;
	preg->state.current = NULL;
	preg->state.index = 0;
	preg->cflags = cflags;
	if (ft_vector(POINTER_TYPE(reg_node), &preg->node_vec) != OK ||
		ft_vector(ATOMIC_TYPE, &preg->sub_vec) != OK)
		return FT_REG_ESPACE;

	// init root:
	if (!(preg->root = new_node(&preg->node_vec, (reg_node){.type = REG_SUB, .parent = NULL})) ||
		(ft_vector(ATOMIC_TYPE, &preg->root->sub) != OK) ||
			ft_vector_push_back(&preg->sub_vec, preg->root) == KO)
		return FT_REG_ESPACE;
	preg->state.current = preg->root;

	// parse:
	while (pattern[preg->state.index])
	{
		int tmp = 0;
		// update context:
		if (preg->state.context & REG_FIRST_IN_BRACKET && preg->state.current->sub.size > 0)
			preg->state.context &= ~REG_FIRST_IN_BRACKET;
		if (ft_strlen(pattern + preg->state.index) == 1) // TODO: replace strlen by wcslen
			preg->state.context |= REG_LAST;
		if (preg->state.index)
			preg->state.context &= ~REG_FIRST;
		// search in handler_map:
		for (size_t j = 0; j < STATIC_ARRAY_SIZE(handler_map); j++)
			if ((!handler_map[j].str || !ft_strncmp(handler_map[j].str, pattern + preg->state.index, ft_strlen(handler_map[j].str))) &&
				!(preg->state.context & handler_map[j].not_mask) && (handler_map[j].mask & preg->state.context) == handler_map[j].mask) // check the mask
			{
				tmp = handler_map[j].handler(preg, pattern);
				break;
			}

		// handle errors:
		if (tmp)
			return tmp;
	}
	if (preg->state.context & REG_ESCAPED)
		return FT_REG_EESCAPE;
	if (preg->state.context & REG_IN_BRACKET)
		return FT_REG_EBRACK;
	if (preg->state.current->parent)
		return FT_REG_EPAREN;
	return 0;
}
