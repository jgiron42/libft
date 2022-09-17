#include "ft_stdio.h"

int	ft_feof(ft_FILE *stream)
{
	return (stream->eof && !stream->rbuflen);
}