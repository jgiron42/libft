#include "internal_printf.h"

int		ft_vsprintf(char *s, const char *format, va_list arg)
{
	ft_FILE stream = {
			.wbuf = s,
			.wbuflen = 0,
			.wbufcap = (size_t)-1,
			.flags = FT_STDIO_STRINGSTREAM,
	};
	int ret = ft_vfprintf(&stream, format, arg);
	if (ret >= 0)
		s[ret] = 0;
	return (ret);
}