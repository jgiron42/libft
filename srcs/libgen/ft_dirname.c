#include "ft_libgen.h"

char  *ft_dirname(char *path)
{
	if (!path || !path[0])
		return ".";
	size_t last = ft_strlen(path) - 1;

	while (last > 0 && path[last] == '/')
	{
		path[last] = 0;
		last--;
	}
	if (last == '/')
		return path;
	while (last > 0 && path[last] != '/')
		last--;
	while (last > 0 && path[last] == '/')
	{
		path[last] = 0;
		last--;
	}
	if (last != 0 || path[last] == '/')
		return path;
	return ".";
}