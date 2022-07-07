#include "ft_stdio.h"

int      ft_fgetpos(ft_FILE *stream, ft_fpos_t *pos)
{
	if (stream->flags == FT_STDIO_STRINGSTREAM)
	{
		*pos = stream->position;
		return 0;
	}
	long ret = ft_ftell(stream);
	if (ret == -1)
		return (-1);
	pos->pos = ret;
	return 0;
}
