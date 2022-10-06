#include "internal_printf.h"

int pad_left(internal_printf *conv, int size)
{
	int padding = 0;
	if (conv->fwidth > size)
		padding = conv->fwidth - size;
	while (padding && !(conv->flags & FT_PRINTF_HYPHEN))
	{
		if (!ft_fputc(conv->flags & FT_PRINTF_ZERO ? '0' : ' ', conv->stream))
			return -1;
		padding--;
	}
	return 0;
}

int pad_right(internal_printf *conv, int size)
{
	int padding = 0;
	if (conv->fwidth > size)
		padding = conv->fwidth - size;
	while (padding && conv->flags & FT_PRINTF_HYPHEN)
	{
		if (!ft_fputc(' ', conv->stream))
			return -1;
		padding--;
	}
	return 0;
}