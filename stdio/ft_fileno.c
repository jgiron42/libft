#include "ft_stdio.h"

int	ft_fileno(ft_FILE *stream)
{
	return (stream->fd);
}