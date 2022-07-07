#include "ft_stdio.h"

int	ft_ferror(ft_FILE *stream)
{
	return (stream->error);
}