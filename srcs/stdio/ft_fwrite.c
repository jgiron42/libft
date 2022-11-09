#include "internal_ft_stdio.h"
#include "ft_string.h"

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
	if (stream->buf_flag != _IONBF && stream->wbuflen + tmp > stream->wbufcap)
	{
		if (ft_fflush(stream))
			return (0);
	}
	if (stream->buf_flag != _IONBF && stream->wbuflen + tmp <= stream->wbufcap) {
		ft_memcpy(stream->wbuf + stream->wbuflen, ptr, tmp);
		stream->wbuflen += tmp;
		stream->position.pos += (ssize_t)tmp;
		if (stream->buf_flag == _IOLBF && ft_memchr(stream->wbuf, '\n', stream->wbuflen) && ft_fflush(stream))
			return 0;
		return (nmemb);
	}
	else
	{
		ssize_t	ret;
		ret = write(stream->fd, ptr, nmemb * size);
		if (ret == -1)
		{
			stream->error = true;
			return (0);
		}
		stream->position.pos += ret;
		return (ret / size);
	}
	// TODO: append
}
