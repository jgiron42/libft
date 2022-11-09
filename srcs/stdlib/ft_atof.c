#include "ft_stdlib.h"

double	ft_atof(const char *nptr)
{
	int errno_save = errno;
	double ret = ft_strtod(nptr, NULL);
	errno = errno_save;
	return (ret);
}