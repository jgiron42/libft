#include "ft_stdlib.h"
#include "ft_string.h"

void	*ft_realloc(void *ptr, size_t size)
{
#if (defined(WHITELIST) && defined(FT_USE_REALLOC))
	return realloc(count, size);
#else
	void *ret = malloc(size);
	if (ret && ptr)
		ft_memcpy(ret, ptr, size);
	return ret;
#endif
}
