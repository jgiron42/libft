#include "internal_printf.h"

int	handle_n(internal_printf *conv, va_list arg)
{
	ft_fpos_t max;

	if (ft_fgetpos(conv->stream, &max) == -1)
		return -1;
	intmax_t val = max.pos - conv->begin;
	void *ptr = va_arg(arg, void *);
	switch (conv->length)
	{
		case (FT_PRINTF_LENGTH_hh):
			*((char *)ptr) = val;
			break;
		case (FT_PRINTF_LENGTH_h):
			*((short *)ptr) = val;
			break;
		case (FT_PRINTF_LENGTH_DEFAULT):
			*((int *)ptr) = val;
			break;
		case (FT_PRINTF_LENGTH_l):
			*((long *)ptr) = val;
			break;
		case (FT_PRINTF_LENGTH_q):
		case (FT_PRINTF_LENGTH_ll):
			*((long long *)ptr) = val;
			break;
		case (FT_PRINTF_LENGTH_j):
			*((intmax_t *)ptr) = val;
			break;
		case (FT_PRINTF_LENGTH_Z):
		case (FT_PRINTF_LENGTH_z):
			*((size_t *)ptr) = val;
			break;
		case (FT_PRINTF_LENGTH_t):
			*((ptrdiff_t *)ptr) = val;
			break;
		default:
			return (-1);
	}
	return (0);
}