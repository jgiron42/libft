#include "internal_ft_stdio.h"
#include "ft_string.h"

ssize_t	ft_get_delim_buffered(char *restrict s, size_t n, ft_FILE *restrict stream, int delim)
{
	if (!n)
		return (0);
	size_t toread = n - 1;
	size_t	ret = 0;
	if (stream->rbuf && stream->rbuflen > 0)
	{
		char *tmp;
		if ((tmp = ft_memchr(stream->rbuf, (unsigned char)delim, stream->rbuflen < toread ? stream->rbuflen : toread)))
			toread = tmp - stream->rbuf + 1;
		if ((size_t)stream->rbuflen > toread)
		{
			ft_memcpy(s, stream->rbuf, toread);
			stream->rbuflen -= toread;
			stream->position.pos += toread;
			ft_memmove(stream->rbuf, stream->rbuf + toread, stream->rbuflen);
			s[toread] = 0;
			return toread;
		}
		ft_memcpy(s, stream->rbuf, stream->rbuflen);
		s += stream->rbuflen;
		*s = 0;
		toread -= stream->rbuflen;
		ret += stream->rbuflen;
		stream->position.pos += stream->rbuflen;
		stream->rbuflen = 0;
	}
	if (stream->flags == FT_STDIO_ISTRINGSTREAM)
	{
		stream->eof = true;
		return ret;
	}
	if (!toread)
		return ret;
	ssize_t tmp = 0;
	char *delim_pos;
	while (!(delim_pos = ft_memchr(s - tmp, (unsigned char)delim, tmp)) && toread > 0)
	{
		tmp = read(stream->fd, s, toread);
		if (tmp == -1)
			return -1;
		if (!tmp)
		{
			if (!ret)
				return 0;
			*s = 0;
			return ret;
		}
		ret += tmp;
		s += tmp;
		toread -= tmp;
		stream->position.pos += tmp;
	}
	*s = 0;
	if (!ret)
		return 0;
	if (delim_pos && delim_pos[1])
	{
		if (ft_ungets(delim_pos + 1, stream))
			return -1;
		ret -= ft_strlen(delim_pos + 1);
		delim_pos[1] = 0;
	}
	return (ret);
}