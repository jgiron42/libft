#include "ft_stdio.h"

int	ft_puts(const char *s)
{
	if (ft_fputs(s, ft_stdout) == ft_EOF || ft_fputc('\n', ft_stdout) == ft_EOF)
		return (ft_EOF);
	return (1);
}