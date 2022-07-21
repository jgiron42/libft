#include "internal_ft_stdio.h"

size_t	ft_fread(void *ptr, size_t size, size_t nmemb, ft_FILE *stream)
{
	if (nmemb == 0 || size == 0)
		return (0);
	size_t toread = size * nmemb;
	size_t	ret = 0;
	if (stream->rbuf && stream->rbuflen > 0)
	{
		if ((size_t)stream->rbuflen > toread)
		{
			ft_memcpy(ptr, stream->rbuf, toread);
			stream->rbuflen -= toread;
			ft_memmove(stream->rbuf, stream->rbuf + (toread), stream->rbuflen);
			return size;
		}
		ft_memcpy(ptr, stream->rbuf, stream->rbuflen);
		ptr += stream->rbuflen;
		toread -= stream->rbuflen;
		ret += stream->rbuflen;
		stream->position.pos += stream->rbuflen;
		stream->rbuflen = 0;
	}
	int tmp = read(stream->fd, ptr, toread);
	if (tmp == -1)
	{
		stream->error = true;
		return (0);
	}
	ret += tmp;
	stream->position.pos += tmp;
	if (!ret)
		stream->eof = true;
	return (ret / size);
}