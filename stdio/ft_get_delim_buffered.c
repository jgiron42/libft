#include "internal_ft_stdio.h"

ssize_t	ft_get_delim_buffered(char *restrict s, size_t n, ft_FILE *restrict stream, int delim)
{
	size_t read_ret;
	char *base = s;
	char *tmp;

	if (stream->rbuf && stream->rbuflen > 0) {
		if ((ft_memchr(stream->rbuf, (unsigned char)delim, stream->rbuflen) || stream->rbuflen > n - 1)) {
			tmp = ft_memccpy(s, stream->rbuf, (unsigned char)delim, n - 1);
			if (!tmp)
				tmp = stream->rbuf + n - 1;
			*tmp = 0;
			stream->rbuflen = tmp - stream->rbuf;
			ft_memmove(stream->rbuf, tmp, stream->rbuflen);
			return n - 1;
		}

		ft_memcpy(s, stream->rbuf, stream->rbuflen);
		n -= stream->rbuflen;
		s += stream->rbuflen;
		stream->rbuflen = 0;
	}
	if (stream->eof)
		return -1;
	if (!(read_ret = ft_fread(s, 1, n - 1, stream)))
		return -1;
	if ((tmp = ft_memchr(s, (unsigned char)delim, read_ret)))
	{
		if ((size_t)((s + read_ret) - tmp )> stream->rbufcap && ft_expand_buf(stream, - ((s + read_ret) - tmp)))
			return (-1);
		ft_memcpy(stream->rbuf, tmp + 1, (s + read_ret) - tmp -1);
		stream->rbuflen = (s + read_ret) - tmp;
		tmp[1] = 0;
	}
	else
		s[read_ret] = 0;
	return (s - base + read_ret);
}