#include "ft_stdio.h"

size_t	ft_fwrite(const void *ptr, size_t size, size_t nmemb, ft_FILE *stream)
{
	if (nmemb == 0 || size == 0)
		return (0);
	if (stream->wbuflen > 0)
		ft_fflush(stream);
	if (stream->wbuf && size * nmemb < stream->rbufcap - stream->wbuflen)
	{
		memcpy(stream->wbuf + stream->wbuflen, ptr, size * nmemb);
		stream->wbuflen += size * nmemb;
		return (0);
	}
	ssize_t	ret = write(stream->fd, ptr, nmemb * size);
	if (ret == -1)
	{
		stream->error = true;
		return (0);
	}
	// TODO: append
	stream->position.pos += ret;
	return (ret / nmemb);
}
