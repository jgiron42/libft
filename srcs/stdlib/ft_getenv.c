#include "ft_stdlib.h"
#include "ft_string.h"

extern char **environ;

char	*ft_getenv(const char *name)
{
	for (int i = 0; environ[i]; i++)
	{
		char *equal = ft_strchr(environ[i], '=');
		if (!equal)
			equal = ft_strchr(environ[i], 0);
		if ((size_t)(equal - environ[i]) == ft_strlen(name) && !ft_strncmp(name, environ[i],  equal - environ[i]))
			return (equal + 1);
	}
	return (NULL);
}