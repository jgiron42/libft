#include "ft_stdio.h"

ssize_t  ft_getline(char **restrict lineptr, size_t *restrict n, ft_FILE *restrict stream)
{
	return ft_getdelim(lineptr,n,'\n', stream);
}