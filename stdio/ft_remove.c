#include "ft_stdio.h"

int	ft_remove(const char *pathname)
{
	if (unlink(pathname) == -1 && errno != EPERM)
		return (-1);
	if (rmdir(pathname) == -1)
		return (-1);
	return(0);
}