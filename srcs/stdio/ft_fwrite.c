#include "internal_ft_stdio.h"

size_t	ft_fwrite(const void *ptr, size_t size, size_t nmemb, ft_FILE *stream)
{
	if (nmemb == 0 || size == 0)
		return (0);
	size_t tmp = size * nmemb;
	if (stream->flags == FT_STDIO_STRINGSTREAM)
	{
		stream->position.pos += (ssize_t)tmp; // TODO: check if this is correct
		if (stream->wbufcap <= stream->wbuflen)
			return 0;
		if (tmp + stream->wbuflen > stream->wbufcap)
			tmp = stream->wbufcap - stream->wbuflen;
		if (tmp) {
			ft_memcpy(stream->wbuf + stream->wbuflen, ptr, tmp);
			stream->wbuflen += tmp;
		}
		return (tmp);
	}
	if (stream->wbuflen + tmp > stream->wbufcap)
		ft_fflush(stream);
	else
	{
		ft_memcpy(stream->wbuf + stream->wbuflen, ptr, tmp);
		stream->wbuflen += tmp;
	}
	if (stream->wbuf && size * nmemb < stream->rbufcap - stream->wbuflen)
	{
		ft_memcpy(stream->wbuf + stream->wbuflen, ptr, size * nmemb);
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
