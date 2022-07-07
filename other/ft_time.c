#include "../libft.h"

time_t	ft_time(time_t *tloc)
{
	time_t	ret;
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1)
		ret = (time_t)-1;
	else
		ret = tv.tv_sec;
	if (tloc)
		*tloc = ret;
	return (ret);
}