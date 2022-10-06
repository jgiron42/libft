#include "ft_stdio.h"

int      ft_fseek(ft_FILE *stream, long offset, int whence)
{
	if (whence != SEEK_CUR && whence != SEEK_END && whence != SEEK_SET)
		return (-1);
	off_t	ret;
	if (ft_fflush(stream) == -1)
		return(-1);
	if ((ret = lseek(stream->fd, offset, whence)) == -1)
		return (-1);
	stream->position.pos = ret;
	return (ret);
}