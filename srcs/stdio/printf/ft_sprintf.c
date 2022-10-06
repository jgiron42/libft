#include "internal_printf.h"

int		ft_sprintf(char *s, const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	int ret = ft_vsprintf(s, format, arg);
	va_end(arg);
	return ret;
}