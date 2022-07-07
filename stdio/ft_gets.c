#include "internal_ft_stdio.h"

char    *ft_gets(char *s)
{
	if (ft_get_delim_buffered(s,SIZE_MAX,ft_stdin, '\n') == -1)
		return NULL;
	return s;
}