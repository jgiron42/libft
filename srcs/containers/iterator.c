#include "containers.h"

size_t		distance(iterator begin, iterator end)
{
	int ret = 0;
	while (begin.metadata.compare(begin.metadata, &begin, &end))
	{
		begin.metadata.increment(&begin);
		ret++;
	}
	return ret;
}

iterator	ft_iterator_advance(iterator it, int n)
{
	if (it.iterator_tag == FT_RANDOM_ACCESS_ITERATOR)
		return *(iterator *)it.metadata.add(&it, n);
	while (n > 0)
	{
		it.metadata.increment(&it);
		n--;
	}
	return it;
}