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

int		easy_way(const ft_regex_t *restrict r, char *s, regexec_t *conf, size_t current_begin)
{
	FA_state	*current = r->graph->begin;
	size_t		i = current_begin;
	bool		match = false;

	if (!current_begin && !(conf->eflags & FT_REG_NOTBOL) && current->d.ascii[FT_RE_BEGIN])
	{
#ifdef REG_DEBUG
		printf("-> begin\n");
#endif
		current = current->d.ascii[FT_RE_BEGIN];
	}

	while (s[i] && current)
	{
		if (current->accept && conf->nmatch)
		{
			conf->pmatch[0].rm_so = current_begin;
			conf->pmatch[0].rm_eo = i;
			match = true;
		}

#ifdef REG_DEBUG
		if (ft_isprint(s[i]))
			printf("-> '%c'\n", (unsigned char)s[i]);
		else
			printf("-> %x\n", (unsigned char)s[i]);
#endif

		if (r->cflags & FT_REG_ICASE)
			current = current->d.ascii[(unsigned char)ft_toupper(s[i])];
		else
			current = current->d.ascii[(unsigned char)s[i]];
		i++;
	}

	if (current && !(conf->eflags & FT_REG_NOTEOL) && current->d.ascii[FT_RE_END])
	{
#ifdef REG_DEBUG
		printf("-> end\n");
#endif
		current = current->d.ascii[FT_RE_END];
	}

	if (current && current->accept && conf->nmatch)
	{
		conf->pmatch[0].rm_so = current_begin;
		conf->pmatch[0].rm_eo = i;
		match = true;
	}
	return match;
}

int    ft_regexec(const ft_regex_t *restrict r, const char *restrict string, size_t nmatch, ft_regmatch_t pmatch[restrict], int eflags)
{
	int ret = FT_REG_NOMATCH;
	regexec_t conf = {
		0,
		0,
		pmatch,
		nmatch,
		eflags
	};
	for (size_t i = 0; i < nmatch; i++)
		pmatch[i] = (ft_regmatch_t){-1, -1, -1, -1};
	for (size_t i = 0; i <= ft_strlen(string);i++) {
		int tmp = 0;
		if (true) // no backref = sweet O(n) algorithm
			tmp = easy_way(r, (char *) string, &conf, i);
		else // Oh no! backrefs!!! O(n^(2k+2)) algorithm *cry in C*
			ft_fprintf(ft_stderr, "AAAAAAAAAAAAAAAAAAAAAAAAAAAH!!!!");
		if (tmp) return 0;
//		printf("%d\n", tmp);
	}
	return ret;
}