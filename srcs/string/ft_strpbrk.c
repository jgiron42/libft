#include "../../includes/libft.h"

char *ft_strpbrk(const char *s, const char *accept)
{
	char *ret = (char *)s;
	while (*ret)
	{
		for (int j = 0; accept[j]; j++)
			if (*ret == accept[j])
				return (ret);
		ret++;
	}
	return (NULL);
}