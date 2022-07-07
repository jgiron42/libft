#include "internal_ft_stdio.h"

char	*ft_fgets(char *restrict s, int n, ft_FILE *restrict stream) // TODO: redo
{
	if (ft_get_delim_buffered(s,n,stream, '\n') == -1)
		return NULL;
	return s;
}