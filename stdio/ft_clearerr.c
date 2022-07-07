#include "ft_stdio.h"

void	ft_clearerr(ft_FILE *stream)
{
	stream->error = false;
	stream->eof = false;
}