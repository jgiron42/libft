#include "internal_printf.h"
#define FT_PRINTF_MAX_NBR_BUF sizeof(uintmax_t) * 3
// for diouxXp

int	handle_integer(internal_printf *conv, va_list arg)
{
	uintmax_t	n;
	bool		is_neg = false;

	bool is_signed = (conv->conversion == 'i' || conv->conversion == 'd');
	int base = 10;
	if (conv->conversion == 'o')
		base = 8;
	else if (conv->conversion == 'x' || conv->conversion == 'X' || conv->conversion == 'p')
		base = 16;

	if (conv->conversion == 'p')
		n = (uintmax_t)(va_arg(arg, void *));
	else if (is_signed)
	{
		intmax_t sn;
		switch (conv->length)
		{
			case (FT_PRINTF_LENGTH_hh):
				sn = (signed char)(va_arg(arg, signed int)); // NOLINT(cert-str34-c)
				break;
			case (FT_PRINTF_LENGTH_h):
				sn = (signed short)(va_arg(arg, signed int));
				break;
			case (FT_PRINTF_LENGTH_DEFAULT):
				sn = (signed int)va_arg(arg, signed int);
				break;
			case (FT_PRINTF_LENGTH_l):
				sn = (signed long)va_arg(arg, signed long);
				break;
			case (FT_PRINTF_LENGTH_q):
			case (FT_PRINTF_LENGTH_ll):
				sn = (signed long long)va_arg(arg, signed long long );
				break;
			case (FT_PRINTF_LENGTH_j):
				sn = (intmax_t)va_arg(arg, intmax_t);
				break;
			case (FT_PRINTF_LENGTH_Z):
			case (FT_PRINTF_LENGTH_z):
				sn = (ssize_t)va_arg(arg, ssize_t);
				break;
			case (FT_PRINTF_LENGTH_t):
				sn = (ptrdiff_t)va_arg(arg, ptrdiff_t);
				break;
			default:
				return (-1);
		}
		if (sn < 0)
		{
			is_neg = true;
			n = -sn;
		}
		else
			n = sn;
	}
	else
	{
		switch (conv->length)
		{
			case (FT_PRINTF_LENGTH_hh):
				n = (unsigned char)(va_arg(arg, unsigned int)); // NOLINT(cert-str34-c)
				break;
			case (FT_PRINTF_LENGTH_h):
				n = (unsigned short)(va_arg(arg, unsigned int));
				break;
			case (FT_PRINTF_LENGTH_DEFAULT):
				n = (unsigned int)va_arg(arg, unsigned int);
				break;
			case (FT_PRINTF_LENGTH_l):
				n = (unsigned long)va_arg(arg, unsigned long);
				break;
			case (FT_PRINTF_LENGTH_q):
			case (FT_PRINTF_LENGTH_ll):
				n = (unsigned long long)va_arg(arg, unsigned long long );
				break;
			case (FT_PRINTF_LENGTH_j):
				n = (uintmax_t)va_arg(arg, uintmax_t);
				break;
			case (FT_PRINTF_LENGTH_Z):
			case (FT_PRINTF_LENGTH_z):
				n = (size_t)va_arg(arg, size_t);
				break;
			case (FT_PRINTF_LENGTH_t):
				n = (ptrdiff_t)va_arg(arg, ptrdiff_t);
				break;
			default:
				return (-1);
		}
	}
	char nbr[FT_PRINTF_MAX_NBR_BUF];
	char *ptr = nbr + FT_PRINTF_MAX_NBR_BUF - 1;

	char *sbase = "0123456789abcdef";
	*ptr = 0;
	do {
		--ptr;
		*ptr = sbase[n % base];
		if (conv->conversion == 'X')
			*ptr = (char)ft_toupper(*ptr);
		n /= base;
	} while (n != 0);
	size_t padding = 0;
	size_t precision = 0;
	size_t size = ft_strlen(ptr);

	if ((ssize_t)size < conv->precision)
	{
		precision = conv->precision - size;
		size = conv->precision;
	}
	else if (conv->conversion == 'o' && conv->flags & FT_PRINTF_SHARP) // place for the zero
	{
		precision++;
		size++;
	}
	if (((conv->conversion == 'x' || conv->conversion == 'X') && conv->flags & FT_PRINTF_SHARP) || conv->conversion == 'p') // place for '0x' or '0X'
		size += 2;
	if (is_neg || (is_signed && (conv->flags & FT_PRINTF_SPACE || conv->flags & FT_PRINTF_PLUS))) // place for the '-', ' ' or '+'
		size++;
	if ((ssize_t)size < conv->fwidth)
		padding = conv->fwidth - size;

	size += padding;

	char *final_buf = malloc(size + 1);
	char *tmp = final_buf;
	if (!final_buf)
		return (-1);
	while (padding && !(conv->flags & FT_PRINTF_HYPHEN))
	{
		*tmp = conv->flags & FT_PRINTF_ZERO ? '0' : ' ';
		tmp++;
		padding--;
	}
	if (is_neg)
	{
		*tmp = '-';
		tmp++;
	}
	else if (is_signed && (conv->flags & FT_PRINTF_SPACE || conv->flags & FT_PRINTF_PLUS))
	{
		*tmp = conv->flags & FT_PRINTF_SPACE ? ' ' : '+';
		tmp++;
	}
	if (((conv->conversion == 'x' || conv->conversion == 'X') && conv->flags & FT_PRINTF_SHARP) || conv->conversion == 'p')
	{
		*tmp = '0';
		tmp[1] = conv->conversion == 'X' ? 'X' : 'x';
		tmp += 2;
	}
	while (precision > 0)
	{
		*tmp = '0';
		tmp++;
		precision--;
	}
	while (*ptr)
	{
		*tmp = *ptr;
		tmp++;
		ptr++;
	}
	while (padding && conv->flags & FT_PRINTF_HYPHEN)
	{
		*tmp = ' ';
		tmp++;
		padding--;
	}
	*tmp = 0;
	return ft_fwrite(final_buf, 1, size, conv->stream) ? 1 : -1;
}