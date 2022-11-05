#include "parse_regexp.h"

reg_node *new_node(container *vec, reg_node  node)
{
	if (ft_vector_push_back(vec, &node) != OK)
		return NULL;
	return ft_vector_back(vec);
}

int	generic_interval(AST *tree, long int begin, long int end)
{
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_REPEATED, .parent = tree->state.current, .repeated = {
			.tok = ft_vector_back(&tree->state.current->sub), // the repeated element is the last from the parent
			.min = begin,
			.max = end
	}});
	ft_vector_pop_back(&tree->state.current->sub); // remove the element from the parent
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tmp->repeated.tok->parent = tmp;
	ft_memcpy(tmp->sub_expr_dependency, tmp->repeated.tok->parent->sub_expr_dependency, sizeof(tmp->sub_expr_dependency));
	return 0;
}

int asterisk_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	int ret = generic_interval(tree, 0, FT_RE_DUP_INF);
	tree->state.index++;
	return ret;
}

int question_mark_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	int ret = generic_interval(tree, 0, 1);
	tree->state.index++;
	return ret;
}

int plus_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	int ret = generic_interval(tree, 1, FT_RE_DUP_INF);
	tree->state.index++;
	return ret;
}

int range_repeat_handler(AST *tree, const char *restrict pattern)
{
	tree->state.index += 1 + !(tree->cflags & FT_REG_EXTENDED);
	if (!ft_strstr(pattern + tree->state.index, &"\\}" [!!(tree->cflags & FT_REG_EXTENDED)]))
		return FT_REG_EBRACE;
	if (ft_strstr(pattern + tree->state.index, &"\\}" [!!(tree->cflags & FT_REG_EXTENDED)]) == pattern + tree->state.index)
		return FT_REG_BADBR;

	char *end;
	long int min = ft_strtol(pattern + tree->state.index, &end, 10);
	long int max = min;
	if (*end == ',') {
		if (ft_isdigit(end[1]))
		{
			max = ft_strtol(end + 1, &end, 10);
			if (max < min || max > FT_RE_DUP_MAX)
				return FT_REG_BADBR;
		}
		else
		{
			max = FT_RE_DUP_INF;
			end++;
		}
	}
	if (min < 0 || min > FT_RE_DUP_MAX || ft_strncmp(end, &"\\}" [!!(tree->cflags & FT_REG_EXTENDED)], 1 + !(tree->cflags & FT_REG_EXTENDED)))
		return FT_REG_BADBR;
	tree->state.index = end - pattern + 1 + !(tree->cflags & FT_REG_EXTENDED);
	return generic_interval(tree, min, max);
}

int open_bracket_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_BRACKET, .parent = tree->state.current});
	if (ft_vector(ATOMIC_TYPE, &tmp->sub) != OK)
		return FT_REG_ESPACE;
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.current = tmp;
	tree->state.context |= REG_IN_BRACKET;
	tree->state.index++;
	if (pattern[tree->state.index] == '^')
	{
		tmp->invert = true;
		tree->state.index++;
	}
	return 0;
}

int close_bracket_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	tree->state.current = tree->state.current->parent;
	tree->state.context &= ~REG_IN_BRACKET;
	tree->state.index++;
	return 0;
}

int open_subexpr_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_SUB, .parent = tree->state.current});
	if (ft_vector(ATOMIC_TYPE, &tmp->sub) != OK)
		return FT_REG_ESPACE;
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tmp->sub_index = tree->sub_vec.size;
	if (ft_vector_push_back(&tree->sub_vec, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.current = tmp;
	tree->state.index += 1 + !(tree->cflags & FT_REG_EXTENDED);
	return 0;
}

int close_subexpr_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	if (!tree->state.current->parent)
		return FT_REG_EPAREN;
	tree->state.current = tree->state.current->parent;
	tree->state.index += 1 + !(tree->cflags & FT_REG_EXTENDED);
	return 0;
}

int back_ref_handler(AST *tree, const char *restrict pattern)
{
	size_t n = pattern[tree->state.index] - '0';
	// check if the referenced node exist
	if (n > tree->sub_vec.size)
		return FT_REG_ESUBREG;
	// check if the referenced sub expression is well closed:
	reg_node *ref = ft_vector_at(&tree->sub_vec,n);
	for (reg_node *tmp = tree->state.current; tmp; tmp = tmp->parent)
		if (ref == tmp)
			return FT_REG_ESUBREG;

	for (reg_node *node = tree->state.current; node; node = node->parent) // now all the ancestors of the node depends on this subexpression
		node->sub_expr_dependency[n] = true;

	for (reg_node *node = ref; node; node = node->parent) // and the ancestor of the refered node depends on this one
		node->sub_expr_dependency[tree->sub_vec.size - 1] = true;

	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_BACK_REF, .back_ref = (int)n, .parent = tree->state.current});
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.index+=2;
	tree->state.context &= ~REG_ESCAPED;
	return 0;
}

int regular_handler(AST *tree, const char *restrict pattern)
{
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_CHAR, ._char = pattern[tree->state.index], .parent = tree->state.current}); // TODO: wide characters
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.context &= ~REG_ESCAPED;
	tree->state.index++;
	return 0;
}

int escaped_regular_handler(AST *tree, const char *restrict pattern)
{
	if (ft_isdigit(pattern[tree->state.index]) && !(tree->cflags & FT_REG_EXTENDED))
		return back_ref_handler(tree, pattern);
	else
		return regular_handler(tree, pattern);
}

int dot_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_DOT, .parent = tree->state.current});
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.index++;
	return 0;
}

int begin_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_BEGIN, .parent = tree->state.current});
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.index++;
	return 0;
}

int end_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_END, .parent = tree->state.current});
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.index++;
	return 0;
}

int slash_handler(AST *tree, const char *restrict pattern)
{
	(void)pattern;
	tree->state.context |= REG_ESCAPED;
	tree->state.index++;
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

int char_class_handler(AST *tree, const char *restrict pattern)
{
	tree->state.index += 2;
	char *tmps;
	int ret = get_val(pattern + tree->state.index, ":]", &tmps);
	if (ret)
		return ret;
	wctype_t type = wctype(tmps);
	free(tmps);
	if (!type)
		return FT_REG_ECTYPE;
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_CLASS, .parent = tree->state.current, .char_class = type});
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.index = ft_strstr(pattern + tree->state.index, ":]") + 2 - pattern;
	return 0;
}

int collating_element_handler(AST *tree, const char *restrict pattern)
{
	tree->state.index += 2;
	char *s;
	int ret = get_val(pattern + tree->state.index, ".]", &s);
	if (ret)
		return ret;
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_COLLATING_ELEMENT, .parent = tree->state.current, .collating_element = s});
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
	{
		free(s);
		return FT_REG_ESPACE;
	}
	tree->state.index = ft_strstr(pattern + tree->state.index, ".]") + 2 - pattern;
	return 0;
}

int equivalence_class_handler(AST *tree, const char *restrict pattern)
{
	tree->state.index += 2;
	char *s;
	int ret = get_val(pattern + tree->state.index, "=]", &s);
	if (ret)
		return ret;
	if (ft_strlen(s) != 1) // TODO: replace by wcslen
		return FT_REG_ECOLLATE;
	free(s);
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_EQUIVALENCE, .equivalence_class = pattern[tree->state.index], .parent = tree->state.current}); // TODO: wide characters
	if (ft_vector_push_back(&tree->state.current->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.index = ft_strstr(pattern + tree->state.index, "=]") + 2 - pattern;
	return 0;
}

int char_range_handler(AST *tree, const char *restrict pattern)
{
	reg_node *last = ft_vector_back(&tree->state.current->sub);
	if (last->type != REG_CHAR || !ft_isascii(last->_char) || !pattern[tree->state.index + 1] || !ft_isascii(pattern[tree->state.index + 1]))
		return regular_handler(tree, pattern);
	last->type = REG_RANGE;
	if (last->_char < pattern[tree->state.index + 1]) {
		last->range.begin = last->_char;
		last->range.end = pattern[tree->state.index + 1];
	}
	else {
		last->range.begin = pattern[tree->state.index + 1];
		last->range.end = last->_char;
	}
	tree->state.index += 2;
	return 0;
}

int	pipe_handler(AST *tree, const char *restrict pattern)
{
	if (!tree->state.current->parent || tree->state.current->parent->type != REG_PIPE)
	{
		reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_PIPE, .parent = tree->state.current->parent});
		if (ft_vector(ATOMIC_TYPE, &tmp->sub) != OK)
			return FT_REG_ESPACE;
		if (ft_vector_push_back(&tmp->sub, tree->state.current) != OK)
			return FT_REG_ESPACE;
		if (!tree->state.current->parent)
			tree->root = tmp;
		tree->state.current->parent = tmp;
	}
	reg_node *tmp = new_node(&tree->node_vec, (reg_node){.type = REG_SUB, .parent = tree->state.current});
	if (ft_vector(ATOMIC_TYPE, &tmp->sub) != OK)
		return FT_REG_ESPACE;
	if (ft_vector_push_back(&tree->state.current->parent->sub, tmp) != OK)
		return FT_REG_ESPACE;
	tree->state.current = tmp;
	tree->state.index++;
	if (pattern[tree->state.index] == '^')
	{
		tmp->invert = true;
		tree->state.index++;
	}
	return 0;
}

int	parse_regexp(ft_regex_t *restrict r, AST *tree, const char *restrict pattern, int cflags)
{
	tree->state.context = 0;
	tree->state.current = NULL;
	tree->state.index = 0;
	r->cflags = cflags;
	tree->cflags = cflags;
	if (ft_vector(POINTER_TYPE(reg_node), &tree->node_vec) != OK ||
		ft_vector(ATOMIC_TYPE, &tree->sub_vec) != OK)
		return FT_REG_ESPACE;

	if (cflags & FT_REG_EXTENDED)
		tree->state.context |= REG_ERE;
	// init root:
	if (!(tree->root = new_node(&tree->node_vec, (reg_node){.type = REG_SUB, .parent = NULL})) ||
		(ft_vector(ATOMIC_TYPE, &tree->root->sub) != OK) ||
		ft_vector_push_back(&tree->sub_vec, tree->root) == KO)
		return FT_REG_ESPACE;
	tree->state.current = tree->root;

	// parse:
	while (pattern[tree->state.index])
	{
		int tmp = 0;
		// update context:
		if ((tree->state.current->type == REG_SUB || tree->state.current->type == REG_BRACKET) && !tree->state.current->sub.size)
			tree->state.context |= REG_FIRST;
		else
			tree->state.context &= ~REG_FIRST;
		// search in handler_map:
		for (size_t j = 0; j < ARRAY_SIZE(handler_map); j++)
			if ((!handler_map[j].str || !ft_strncmp(handler_map[j].str, pattern + tree->state.index, ft_strlen(handler_map[j].str))) &&
				!(tree->state.context & handler_map[j].not_mask) && (handler_map[j].mask & tree->state.context) == handler_map[j].mask) // check the mask
			{
				tmp = handler_map[j].handler(tree, pattern);
				break;
			}

		// handle errors:
		if (tmp)
			return tmp;
	}
	r->re_nsub = tree->sub_vec.size - 1;
	if (tree->state.context & REG_ESCAPED)
		return FT_REG_EESCAPE;
	if (tree->state.context & REG_IN_BRACKET)
		return FT_REG_EBRACK;
	if (tree->state.current->parent)
		return FT_REG_EPAREN;
	return 0;
}

void	destroy_tree(AST *tree)
{
	for_val_in(reg_node *node, tree->node_vec)
		if (node->sub.init)
			node->sub.destroy(&node->sub);
	ft_vector_destructor(&tree->node_vec);
	ft_vector_destructor(&tree->sub_vec);
}
