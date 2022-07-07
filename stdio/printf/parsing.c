#include "internal_printf.h"

int	parse_flag(internal_printf *conv, va_list arg)
{
	(void)arg;
	char *current;
	while ((current = ft_strchr(ft_printf_flag_char, **conv->format)))
	{
		conv->flags |= 1 << (current -ft_printf_flag_char);
		(*conv->format)++;
	}
	return (0);
}

int	parse_fwidth(internal_printf *conv, va_list arg)
{
	(void)arg;
	if (**conv->format == '*')
	{
		conv->fwidth = va_arg(arg, int);
		(*conv->format)++;
		return (0);
	}
	if (!ft_isdigit(**conv->format))
		return 0;
	errno = 0;
	conv->fwidth = ft_strtol(*conv->format, (char **)conv->format, 10);
	if (errno)
		return (-1);
	return (0);
}

int	parse_precision(internal_printf *conv, va_list arg)
{
	(void)arg;
	if (**conv->format != '.')
		return 0;
	(*conv->format)++;
	if (**conv->format == '*')
	{
		conv->precision = va_arg(arg, int);
		(*conv->format)++;
		return (0);
	}
	if (!ft_isdigit(**conv->format))
		return -1;
	errno = 0;
	conv->precision = ft_strtol(*conv->format, (char **)conv->format, 10);
	if (errno)
		return (-1);
	return (0);
}

int	parse_length(internal_printf *conv, va_list arg)
{
	(void)arg;
	int i = 0;
	while (ft_printf_length_modifier_char[i] &&
	ft_strncmp(*conv->format, ft_printf_length_modifier_char[i], ft_strlen(ft_printf_length_modifier_char[i])))
		i++;
	if (ft_printf_length_modifier_char[i])
	{
		conv->length = i - 1;
		*conv->format += ft_strlen(ft_printf_length_modifier_char[i]);
	}
	return 0;
}

int	parse_conv(internal_printf *conv, va_list arg)
{
	(void)arg;
	conv->conversion = **conv->format;
	return (0);
}