#include "ft_ctype.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f');
}
