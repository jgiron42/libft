#include "internal_printf.h"

int	handle_m(internal_printf *conv, va_list arg)
{
	(void)arg;
#ifdef ENABLE_STRERROR
	char *str = strerror(errno);
	size_t len = ft_strlen(str);
	if (pad_left(conv, len) == -1)
		return -1;
	if (!ft_fputs(str, conv->stream))
		return -1;
	if (pad_right(conv, len) == -1)
		return -1;
#else
	(void)conv;
#endif
	return (0);
}