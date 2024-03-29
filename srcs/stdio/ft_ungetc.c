#include "internal_ft_stdio.h"
#include "ft_string.h"

int ft_ungetc(int c, ft_FILE *stream) // bad implementation
{
	if (stream->rbufcap <= stream->rbuflen && ft_expand_buf(stream, 1))
		return 1;
	ft_memmove(stream->rbuf + 1, stream->rbuf, stream->rbuflen);
	*stream->rbuf = (unsigned char)c;
	stream->rbuflen++;
	stream->position.pos--;
	stream->eof = false;
	return 0;
}