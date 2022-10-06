#include "internal_ft_stdio.h"

int		ft_fgetc(ft_FILE *stream)
{
	if (stream->eof)
		return (ft_EOF);
	unsigned char c;
	if (ft_fread(&c, 1, 1, stream) == 0)
		return (ft_EOF);
	return (c);
}