#include "ft_stdio.h"

void	ft_perror(const char *prefix)
{
	if (prefix && *prefix)
	{
		char *error = strerror(errno);
		ft_fputs(prefix, ft_stderr);
		ft_fputs(": ", ft_stderr);
		ft_fputs(error, ft_stderr);
	}
	else
		ft_fputs(strerror(errno), ft_stderr);
}