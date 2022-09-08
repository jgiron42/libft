#include "internal_ft_stdio.h"

ssize_t	ft_get_delim_buffered(char *restrict s, size_t n, ft_FILE *restrict stream, int delim)
{
	size_t read_ret;
	char *tmp;

	if (stream->eof)
		return -1;
	if (!(read_ret = ft_fread(s, 1, n - 1, stream)))
		return -1;
	if ((tmp = ft_memchr(s, (unsigned char)delim, read_ret)))
	{
		if ((size_t)((s + read_ret) - tmp ) > stream->rbufcap &&
		ft_expand_buf(stream, ((s + read_ret) - tmp)))
			return (-1);
		stream->rbuflen = s + read_ret - tmp - 1;
		ft_memcpy(stream->rbuf, tmp + 1, stream->rbuflen);
		tmp[1] = 0;
		return (tmp - s);
	}
	else
		s[read_ret] = 0;
	return (read_ret);
}