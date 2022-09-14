#include "internal_ft_regex.h"

bool	match_one_char(const ft_regex_t *restrict r, reg_node *node, char *s, size_t end)
{
	register bool match = false;
	switch (node->type)
	{
		case REG_DOT:
			match = !(r->cflags & FT_REG_NEWLINE) || s[end] != '\n'; // TODO: wc
			break;
		case REG_CHAR:
//			printf("    c = %c, s[%zu] = %c\n", node->_char, end, s[end]);
			match = node->_char == s[end]; // TODO: wc
			break;
		case REG_EQUIVALENCE:
			match = (!strcoll((char[2]) {s[end], 0}, (char[2]) {node->equivalence_class, 0}));
			break;
		case REG_CLASS:
			match = (iswctype(s[end], node->char_class)) != 0;
			break;
		case REG_RANGE:
			match = (s[end] >= node->range.begin && s[end] <= node->range.end);
			break;
		case REG_BRACKET:
		{
			for (size_t j = 0; j < node->sub.size; j++) {
				reg_node *tmp = ft_vector_at(&node->sub, j);
				if (match_one_char(r, tmp, s, end)) {
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

int		easy_way(const ft_regex_t *restrict r, char *s, regexec_t *conf)
{
	reg_node	*parent = r->root;
	size_t		subexpr_depth = 0;
	size_t		interval_depth = 0;
	parent->current = 0;
	reg_node *child = NULL;
	size_t end = conf->begin;
	bool match = true;
	if (conf->nmatch > 0 && !(r->cflags & FT_REG_NOSUB))
		conf->pmatch[0].tmp_so = end;
	begin:
	if (parent->type == REG_SUB)
	{
//		printf("=> %zu %p\n", parent->sub_index, parent->sub.vector.data);
		child = ft_vector_at(&parent->sub, parent->current);
		match = true;
	}
	else if (parent->type == REG_REPEATED)
	{
		child = parent->repeated.tok;
		match = true;
	}
	switch (child->type) {
		case REG_DOT:
		case REG_CHAR:
		case REG_EQUIVALENCE:
		case REG_CLASS:
		case REG_BRACKET:
			match = match_one_char(r, child, s, end);
			if (match)
				end++;
			break;
		case REG_BEGIN:
			if (conf->eflags & FT_REG_NEWLINE)
				;
			else if (conf->eflags & FT_REG_NOTBOL || end != 0)
				match = 0;
			else
				match = 1;
			break;
		case REG_SUB:
			subexpr_depth++;
			interval_depth--;
		case REG_REPEATED:
			interval_depth++;
//			for (size_t i = 0; i < subexpr_depth; i++)
//				printf(" ");
			printf("%c %zu %zu %zu %zu\n", s[end], end, child->sub_index, subexpr_depth, interval_depth);
			if (child->type == REG_SUB && child->sub_index < conf->nmatch && !(r->cflags & FT_REG_NOSUB)
				&& ((subexpr_depth - 1 == 0) || (interval_depth == 0)))
			{
//				printf("coucou\n");
				conf->pmatch[child->sub_index].tmp_so = end;
			}
			parent = child;
			parent->current = 0;
			match = true;
			goto begin;
		default:
			printf("Should not be reached\n");
	}
	end:
	conf->end = end;
	if (match && child->type == REG_SUB && child->sub_index < conf->nmatch && !(r->cflags & FT_REG_NOSUB))
		conf->pmatch[child->sub_index].tmp_eo = end;
	if (!parent)
	{
		if (conf->nmatch > 0 && !(r->cflags & FT_REG_NOSUB))
			conf->pmatch[0].tmp_eo = end;
		return match ? 0 : FT_REG_NOMATCH;
	}
//	printf("-> p: %d c: %d matched: %d\n",parent->type, child->type, match);
	if (parent->type == REG_SUB)
	{
//		printf("=> current: %zu, parent.sub.size: %zu\n", parent->current, parent->sub.size);
		if (parent->current >= (ssize_t)parent->sub.size - 1 || !match)
		{
			child = parent;
			parent = parent->parent;
			subexpr_depth--;
			goto end;
		} else {
			parent->current++;
			goto begin;
		}
	}
	else if (parent->type == REG_REPEATED)
	{
		if (match)
			parent->current++;
		if (!match || parent->current == parent->repeated.max)
		{
//			printf("=> %zd %zd %zd\n",parent->current, parent->repeated.min, parent->matched);
			match = true;
			if (parent->current < parent->repeated.min)
				parent->current = 0;
			for (int i = 0; i < parent->sub_expr_dependency)
			child = parent;
			parent = parent->parent;
			interval_depth--;
			goto end;
		}
		goto begin;
	}
	printf("Should not be reached\n");
	return 0;
}

int    ft_regexec(const ft_regex_t *restrict r, const char *restrict string, size_t nmatch, ft_regmatch_t pmatch[restrict], int eflags)
{
	int ret = FT_REG_NOMATCH;
	size_t max = 0;
	regexec_t conf = {
		0,
		0,
		pmatch,
		nmatch,
		eflags
	};
	for (size_t i = 0; i < nmatch; i++)
		pmatch[i] = (ft_regmatch_t){-1, -1, -1, -1};
	for (size_t i = 0; string[i];i++) {
		conf.begin = i;
		int tmp = 0;
		if (!ft_memchr(r->root->sub_expr_dependency, true, sizeof r->root->sub_expr_dependency)) // no backref = sweet O(n) algorithm
			tmp = easy_way(r, (char *) string, &conf);
		else // Oh no! backrefs!!! O(n^(2k+2)) algorithm *cry in C*
			ft_fprintf(ft_stderr, "AAAAAAAAAAAAAAAAAAAAAAAAAAAH!!!!");
		if (!tmp && (conf.end - conf.begin > max || max == 0))
		{
			ret = 0;
			max = conf.end - conf.begin;
			if (!(r->cflags & FT_REG_NOSUB) && nmatch > 0)
				for (size_t j = 0; j < nmatch; j++)
					pmatch[j] = (ft_regmatch_t) {.rm_so = pmatch[j].tmp_so, .rm_eo = pmatch[j].tmp_eo, .tmp_so = -1, .tmp_eo = -1};
			else
				break;
		}
	}
	return ret;
}