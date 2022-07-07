#include "../libft.h"

void	*ft_lazy_realloc(void *ptr, size_t size)
{
	if (!ptr)
		return malloc(size);
	void *ret = malloc(size);
	if (!ret)
		return NULL;
	ft_memcpy(ret, ptr, size);
	return (ret);
}