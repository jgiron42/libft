#include "internal_ft_regex.h"
#include "ft_ctype.h"
#include "ft_stdio.h"
#include "ft_string.h"
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