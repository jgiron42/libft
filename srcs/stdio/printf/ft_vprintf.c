#include "internal_printf.h"

int		ft_vprintf(const char *format, va_list arg)
{
	return (ft_vfprintf(ft_stdout, format, arg));
}