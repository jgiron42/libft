#include "internal_ft_regex.h"
#include "ft_strings.h"

void   ft_regfree(ft_regex_t *r)
{
	if (r->graph)
	{
		destroy_automaton(r->graph);
		free(r->graph);
		r->graph = NULL;
	}
	ft_bzero(r, sizeof (ft_regex_t));
}