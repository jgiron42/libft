#include "../../includes/libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	int ret = 0;
	while (s[ret])
	{
		if (!ft_strchr(accept, s[ret]))
			break;
		ret++;
	}
	return (ret);
}