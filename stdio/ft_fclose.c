#include "ft_stdio.h"

int ft_fclose(ft_FILE *stream)
{
	ft_fflush(stream);
	if (close(stream->fd) == -1)
		return (ft_EOF);
	if (stream->next)
		stream->next->prev = stream->prev;
	else
		ft_last_file = stream->prev;
	if (stream->prev)
		stream->prev->next = stream->next;
	free(stream->rbuf);
	free(stream->wbuf);
	if (!stream->dontfree)
		free(stream);
	else
		stream->fd = -1;
	return (0);
}