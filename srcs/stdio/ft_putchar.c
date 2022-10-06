#include "ft_stdio.h"

int ft_putchar(int c)
{
	return ft_putc(c, ft_stdout);
}