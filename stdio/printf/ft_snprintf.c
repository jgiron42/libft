#include "internal_printf.h"

int		ft_snprintf(char *s, size_t size, const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	int ret = ft_vsnprintf(s, size, format, arg);
	va_end(arg);
	return ret;
}