#include "internal_ft_stdio.h"

int	ft_expand_buf(ft_FILE *stream, int n)
{
	if (stream->rbufcap < stream->rbuflen + n)
	{
		char *tmp = malloc(stream->rbufcap + n);
		if (!tmp)
			return 1;
		if (stream->rbuf)
		{
			ft_memcpy(tmp, stream->rbuf, stream->rbuflen);
			free(stream->rbuf);
		}
		stream->rbufcap = stream->rbufcap + n;
		stream->rbuf = tmp;
	}
	return 0;
}