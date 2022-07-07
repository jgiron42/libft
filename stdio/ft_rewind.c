#include "ft_stdio.h"

void	ft_rewind(ft_FILE *stream)
{
	(void)ft_fseek(stream, 0L, SEEK_SET);
	ft_clearerr(stream);
}