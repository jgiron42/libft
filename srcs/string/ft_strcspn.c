#include "ft_string.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	int ret = 0;
	while (s[ret])
	{
		if (ft_strchr(reject, s[ret]))
			break;
		ret++;
	}
	return (ret);
}