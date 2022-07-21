#include "internal_ft_stdio.h"

int      ft_fputc(int c, ft_FILE *stream)
{
	unsigned char cc = c;

	if (ft_fwrite(&cc, 1, 1, stream) != 1)
		return (ft_EOF);
	return cc;
}