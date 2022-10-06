#include "../../includes/libft.h"

char	*ft_append(char **str, char *to_append)
{
	char *ret;
	if (*str)
		ret = ft_strjoin(*str, to_append);
	else
		ret = ft_strdup(to_append);
	if (!ret)
		return NULL;
	free(*str);
	*str = ret;
	return (ret);
}