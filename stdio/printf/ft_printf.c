#include "internal_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	int ret = ft_vprintf(format, arg);
	va_end(arg);
	return ret;
}