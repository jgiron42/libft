#include "internal_printf.h"
#include "ft_string.h"

int	handle_string(internal_printf *conv, va_list arg)
{
	char *str = va_arg(arg, char *);
	size_t len = ft_strlen(str);
	if (pad_left(conv, len) == -1)
		return -1;
	if (!ft_fputs(str, conv->stream))
		return -1;
	if (pad_right(conv, len) == -1)
		return -1;
	return 0;
}