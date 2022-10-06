#include "internal_ft_stdio.h"

void ft_setbuf(ft_FILE *restrict stream, char *restrict buf)
{
	if (buf)
		ft_setvbuf(stream, buf, _IOFBF,BUFSIZ);
	else
		ft_setvbuf(stream, buf, _IONBF,BUFSIZ);
}