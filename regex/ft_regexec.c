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

int		easy_way(const ft_regex_t *restrict r, char *s, int eflags)
{
	reg_node *parent = r->root;
	parent->current = 0;
	parent->matched = 1;
	reg_node *child = NULL;
	begin:
	if (parent->type == REG_SUB)
	{
		child = ft_vector_at(&parent->sub, parent->current);
		child->matched = 1;
		child->begin = parent->end;
		child->end = child->begin;
	}
	else if (parent->type == REG_REPEATED)
	{
		child = parent->repeated.tok;
		child->matched = 1;
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
			if (child->matched)
				child->end++;
			break;
		case REG_BEGIN:
			if (eflags & FT_REG_NEWLINE)
				;
			else if (eflags & FT_REG_NOTBOL || child->end != 0)
				child->matched = 0;
			else
				child->matched = 1;
			break;
		case REG_SUB:
		case REG_REPEATED:
		{
			parent = child;
			parent->current = 0;
			parent->matched = 1;
			goto begin;
		}
		default:
			return false;
	}
	end:
	if (!parent)
		return child->matched ? 0 : FT_REG_NOMATCH;
//	printf("-> p: %d c: %d matched: %zd\n",parent->type, child->type, child->matched);
	parent->end = child->end;
	if (parent->type == REG_SUB)
	{
		parent->matched &= child->matched;
//		printf("=> current: %zu, parent.sub.size: %zu\n", parent->current, parent->sub.size);
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
			parent->current++;
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
	int ret = FT_REG_NOMATCH;
	ft_regmatch_t max = {-1, -1};
	for (size_t i = 0; string[i];i++) {
		r->root->end = r->root->begin = i;
		int tmp = 0;
		if (!ft_memchr(r->root->sub_expr_dependency, true, sizeof r->root->sub_expr_dependency)) // no backref = sweet O(n) algorithm
			tmp = easy_way(r, (char *) string, eflags);
		else // Oh no! backrefs!!! O(n^(2k+2)) algorithm *cry in C*
			ft_fprintf(ft_stderr, "AAAAAAAAAAAAAAAAAAAAAAAAAAAH!!!!");
		if (!tmp && (r->root->end - r->root->begin > max.rm_eo - max.rm_so || (max.rm_so == (ft_regoff_t)-1 && max.rm_eo == (ft_regoff_t)-1)))
		{
			max.rm_so = r->root->begin;
			max.rm_eo = r->root->end;
			for (size_t j = 0; j < nmatch; j++)
			{
				if (j < r->sub_vec.size)
				{
					reg_node *current = ft_vector_at(&r->sub_vec, j);
					pmatch[j] = (ft_regmatch_t){current->begin, current->end};
				}
				else
					pmatch[j] = (ft_regmatch_t){-1, -1};
			}
			ret = 0;
		}
	}
	return ret;
}