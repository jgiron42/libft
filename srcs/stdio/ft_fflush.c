#include "internal_ft_stdio.h"

int ft_fflush(ft_FILE *stream)
{
	if (ft_stdin->fd == -1)
	{
		errno = EBADFD;
		return (ft_EOF);
	}
	if (!stream)
	{
		ft_fflush(ft_stdin);
		ft_fflush(ft_stdout);
		ft_fflush(ft_stderr);
		ft_FILE *tmp = ft_last_file;
		while (tmp)
		{
			if (ft_fflush(tmp) == ft_EOF)
				return ft_EOF;
			tmp = tmp->prev;
		}
		return 0;
	}
	if (stream->flags != FT_STDIO_R)
	{
		ssize_t tmp = 0;
		if (stream->wbuf && (tmp = write(stream->fd, stream->wbuf, stream->wbuflen)) == -1)
		{
			stream->error = true;
			return ft_EOF;
		}
		if ((size_t)tmp != stream->wbuflen)
			ft_memmove(stream->wbuf, stream->wbuf + tmp, stream->wbuflen - tmp);
		stream->wbuflen -= tmp;
	}
	if (stream->rbuf)
	{
#if (defined(WHITELIST) && defined(FT_USE_LSEEK)) || (!defined(WHITELIST) && !defined(FT_NO_LSEEK))
		if (lseek(stream->fd, -stream->rbuflen, SEEK_SET) == -1)
			return (ft_EOF);
#endif
		stream->rbuf = NULL;
		stream->rbuflen = 0;
	}
	return (0);
}