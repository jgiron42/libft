#include "ft_stdio.h"

int		ft_rename(const char *oldpath, const char *newpath)
{
	int save_errno;
	if (link(oldpath, newpath) == -1)
	{
		if (errno == EEXIST) {
			if (unlink(newpath) < 0 || link(oldpath, newpath) < 0)
				return -1;
		}
		else
			return -1;
	}
	if (unlink(oldpath) == -1)
	{
		save_errno = errno;
		if (unlink(newpath) == 0)
			errno = save_errno;
		return -1;
	}
	return 0;
}