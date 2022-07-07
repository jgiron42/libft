#include "internal_printf.h"

int	handle_char(internal_printf *conv, va_list arg)
{
	if (pad_left(conv, 1) == -1)
		return -1;
	if (!ft_fputc(va_arg(arg, char), conv->stream))
		return -1;
	if (pad_right(conv, 1) == -1)
		return -1;
	return 0;
}