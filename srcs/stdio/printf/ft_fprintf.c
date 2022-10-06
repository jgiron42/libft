#include "internal_printf.h"

int ft_fprintf(ft_FILE *stream, const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	int ret = ft_vfprintf(stream, format, arg);
	va_end(arg);
	return ret;
}