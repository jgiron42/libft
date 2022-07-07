#include "internal_printf.h"

int	handle_percent(internal_printf *conv, va_list arg)
{
	(void)conv;
	(void)arg;
	return (ft_fputc('%', ft_stdin) == ft_EOF ? -1 : 0);
}