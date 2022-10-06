#include "../../includes/libft.h"

double	ft_atof(const char *nptr)
{
	int errno_save = errno;
	double ret = strtod(nptr, NULL);
	errno = errno_save;
	return (ret);
}