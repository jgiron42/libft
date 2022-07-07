#include "ft_stdio.h"

int      ft_putc(int c, ft_FILE *stream)
{
	return (ft_fputc(c, stream));
}
