#include "ft_libgen.h"

char  *ft_basename(char *path)
{
	if (!path[0])
		return ".";
	size_t last = ft_strlen(path) - 1;

	while (last > 0 && path[last] == '/')
	{
		path[last] = 0;
		last--;
	}
	if (last == 0)
		return path;
	while (last > 0 && path[last] != '/')
		last--;
	if (path[last] == '/')
		return path + last + 1;
	return path;
}