#include "internal_ft_stdio.h"
#include "ft_string.h"

int		ft_setvbuf(ft_FILE *restrict stream, char *restrict buf, int type, size_t size)
{
	char *old_buf = NULL;
	if (stream->wbuf && stream->free_wbuf)
		old_buf = stream->wbuf;
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
		if (old_buf) {
			if (stream->wbuflen <= size)
				ft_memcpy(stream->wbuf, old_buf, stream->wbuflen);
			else {
				ft_memcpy(stream->wbuf, old_buf, size);
				stream->wbuflen = size;
			}
		}
		else
			stream->wbuflen = 0;
		stream->wbufcap = size;
	}
	else
		stream->wbuf = NULL;
	free(old_buf);
	stream->buf_flag = type;
	return 0;
}