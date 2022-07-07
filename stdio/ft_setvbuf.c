#include "internal_ft_stdio.h"

int		ft_setvbuf(ft_FILE *restrict stream, char *restrict buf, int type, size_t size)
{
	if (stream->wbuf && stream->free_wbuf)
		free(stream->wbuf);
	if (type != _IONBF)
	{
		if (buf)
		{
			stream->wbuf = buf;
			stream->free_wbuf = false;
		}
		else
		{
			buf = malloc(size);
			if (!buf)
				return -1;
			stream->wbuf = buf;
			stream->free_wbuf = true;
		}
		stream->wbuflen = size;
	}
	else
		stream->wbuf = NULL;
	stream->buf_flag = type;
	return 0;
}