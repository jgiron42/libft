#include "internal_ft_regex.h"

void   ft_regfree(ft_regex_t *r)
{
	ft_vector_destructor(&r->node_vec);
	ft_vector_destructor(&r->sub_vec);
	ft_bzero(r, sizeof (ft_regex_t));
}