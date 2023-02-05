#include "internal_printf.h"

int		handle_conversion(ft_FILE *restrict stream, const char *restrict* format, va_list arg, size_t tmp)
{
	internal_printf conv ={.stream = stream, .format = format, .begin = tmp};
	++*format;
	if (parse_flag(&conv, arg) == -1 ||
		parse_fwidth(&conv, arg) == -1 ||
		parse_precision(&conv, arg) == -1 ||
		parse_length(&conv, arg) == -1 ||
		parse_conv(&conv, arg) == -1)
		return ( -1);
	switch (conv.conversion)
	{
		case 'i':
		case 'd':
		case 'u':
		case 'x':
		case 'X':
		case 'o':
		case 'p':
			handle_integer(&conv, arg);
			break;
		case 'c':
			handle_char(&conv, arg);
			break;
		case 's':
			handle_string(&conv, arg);
			break;
		case 'm':
			handle_m(&conv, arg);
			break;
		case 'n':
			handle_n(&conv, arg);
			break;
		case '%':
			handle_percent(&conv, arg);
			break;
			/*
			 * e E f F g G a A
			 */
	}
	return 1;
}

int      ft_vfprintf(ft_FILE *restrict stream, const char *restrict format, va_list arg)
{
	ft_fpos_t tmp;
	size_t			pos;
	if (ft_fgetpos(stream, &tmp) == -1)
		return -1;
	pos = tmp.pos;
	while (*format)
	{
		if (*format == '%')
		{
			if (handle_conversion(stream, &format, arg, pos) == -1)
				return -1;
		}
		else
			ft_fputc(*format, stream);
		format++;
	}
	if (ft_fgetpos(stream, &tmp) == -1)
		return -1;
	return (tmp.pos - pos);
}
