#include "ft_stdio.h"

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
		if (stream->wbuf && (stream->position.pos = write(stream->fd, stream->wbuf, stream->wbuflen)) == -1)
			return ft_EOF;
		free(stream->wbuf);
		stream->wbuf = NULL;
		stream->wbuflen = 0;
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