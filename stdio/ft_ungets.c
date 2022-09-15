#include "internal_ft_stdio.h"

int ft_ungets(const char *s, ft_FILE *stream) // bad implementation
{
	size_t len = ft_strlen(s);
	if (stream->rbufcap < stream->rbuflen + len && ft_expand_buf(stream, len))
		return 1;
	ft_memmove(stream->rbuf + len, stream->rbuf, stream->rbuflen);
	ft_memcpy(stream->rbuf, s, len);
	stream->rbuflen += len;
	stream->position.pos -= len;
	return 0;
}