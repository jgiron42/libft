#include "libft.h"

/**
 * check if the program is needed to be posixly correct with the POSIXLY_CORRECT and POSIX_ME_HARDER environment variables
 * @return true if one of the posix variables is set otherwise false
 */
bool	ft_posixly_correct()
{
	static int ret = -1;

	if (ret != -1)
		return ((bool)ret);
	for (int i = 0; environ[i]; i++)
	{
		char *equal = ft_strchr(environ[i], '=');
		if (!equal)
			continue;
		if (!ft_strncmp(environ[i], "POSIXLY_CORRECT", equal - environ[i]) ||
			!ft_strncmp(environ[i], "POSIX_ME_HARDER", equal - environ[i]))
		{
			ret = 1;
			return (true);
		}
	}
	ret = 0;
	return false;
}