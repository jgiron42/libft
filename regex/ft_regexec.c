#include "internal_ft_regex.h"

bool	match_one_char(const ft_regex_t *restrict r, reg_node *node, char *s)
{
	register bool match = false;
	switch (node->type)
	{
		case REG_DOT:
			match = !(r->cflags & FT_REG_NEWLINE) || s[node->end] != '\n'; // TODO: wc
			break;
		case REG_CHAR:
//			printf("    c = %c, s[%zu] = %c\n", node->_char, node->end, s[node->end]);
			match = node->_char == s[node->end]; // TODO: wc
			break;
		case REG_EQUIVALENCE:
			match = (!strcoll((char[2]) {s[node->end], 0}, (char[2]) {node->equivalence_class, 0}));
			break;
		case REG_CLASS:
			match = (iswctype(s[node->end], node->char_class)) != 0;
			break;
		case REG_RANGE:
			match = (s[node->end] >= node->range.begin && s[node->end] <= node->range.end);
			break;
		case REG_BRACKET:
		{
			for (size_t j = 0; j < node->sub.size; j++) {
				reg_node *tmp = ft_vector_at(&node->sub, j);
				tmp->begin = node->end;
				tmp->end = node->end;
				if (match_one_char(r, tmp, s)) {
					match = true;
					break;
				}
			}
			break;
		}
		default:
			return 0;
	}
	return match;
}

int		easy_way(const ft_regex_t *restrict r, char *s)
{
	reg_node *parent = r->root;
	parent->current = 0;
	parent->begin = 0;
	parent->end = 0;
	reg_node *child = NULL;
	begin:
	if (parent->type == REG_SUB)
	{
		child = ft_vector_at(&parent->sub, parent->current);
		child->begin = parent->end;
		child->end = child->begin;
	}
	else if (parent->type == REG_REPEATED)
	{
		child = parent->repeated.tok;
		child->begin = parent->end;
		child->end = parent->end;
	}
	switch (child->type) {
		case REG_DOT:
		case REG_CHAR:
		case REG_EQUIVALENCE:
		case REG_CLASS:
		case REG_BRACKET:
			child->matched = match_one_char(r, child, s);
			child->end += child->matched;
			break;
		case REG_SUB:
		case REG_REPEATED:
		{
			parent = child;
			parent->current = 0;
			parent->matched = 0;
			goto begin;
		}
		default:
			return false;
	}
	end:
	if (!parent)
		return child->matched;
//	printf("-> p: %d c: %d matched: %zd\n",parent->type, child->type, child->matched);
	parent->end += child->matched;
	if (parent->type == REG_SUB)
	{
		if (!child->matched)
			parent->matched = 0;
		else
			parent->matched += child->matched;
		if (parent->current >= (ssize_t)parent->sub.size - 1 || !child->matched) {
			child = parent;
			parent = parent->parent;
			goto end;
		} else {
			parent->current++;
			goto begin;
		}
	}
	else if (parent->type == REG_REPEATED)
	{
		if (child->matched)
		{
			parent->current++;
			parent->matched += child->matched;
		}
		if (!child->matched || parent->current == parent->repeated.max)
		{
//			printf("=> %zd %zd %zd\n",parent->current, parent->repeated.min, parent->matched);
			if (parent->current < parent->repeated.min)
			{
				parent->matched = 0; // TODO: revoir
				parent->current = 0;
			}
			child = parent;
			parent = parent->parent;
			goto end;
		}
		goto begin;
	}
	return 0;
}

int    ft_regexec(const ft_regex_t *restrict r, const char *restrict string, size_t nmatch, ft_regmatch_t pmatch[restrict], int eflags)
{
	(void)eflags;
	int ret = 0;
	if (!ft_memchr(r->root->sub_expr_dependency, true, sizeof r->root->sub_expr_dependency)) // no backref = sweet O(n) algorithm
		ret = easy_way(r, (char *)string);
	else // Oh no! backrefs!!! O(n^(2k+2)) algorithm *cry in C*
		ft_fprintf(ft_stderr, "AAAAAAAAAAAAAAAAAAAAAAAAAAAH!!!!");
	if (!ret)
		for (size_t i = 0; i < nmatch; i++)
		{
			if (i < r->sub_vec.size)
			{
				reg_node *current = ft_vector_at(&r->sub_vec, i);
				pmatch[i] = (ft_regmatch_t){current->begin, current->end};
			}
			else
				pmatch[i] = (ft_regmatch_t){-1, -1};
		}
	return ret;
}