#include "ft_stdio.h"

long     ft_ftell(ft_FILE *stream)
{
	return (stream->position.pos);
}