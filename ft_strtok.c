#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char *current = NULL;
	char *ret = NULL;

	if (str)
		current = str;
	else if (!current)
		return (NULL);
	current += ft_strcspn(current, delim);
	if (!*current)
	{
		current = NULL;
		return (NULL);
	}
	ret = current;
	current = ft_strpbrk(current, delim);
	if (current)
	{
		*current = 0;
		current++;
	}
	return (ret);
}