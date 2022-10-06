#include "ft_stdio.h"

int      ft_fsetpos(ft_FILE *stream, const ft_fpos_t *pos)
{
	return ft_fseek(stream, pos->pos, SEEK_SET);
}