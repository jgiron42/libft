#include "algorithms.h"

// return true if the first range is lexicographically less than the second, otherwise false.
bool	ft_lexicographical_compare(iterator lbegin, iterator lend, iterator rbegin, iterator rend)
{
	while (lbegin.metadata.compare(lbegin.metadata, &lbegin, &lend) &&
			rbegin.metadata.compare(rbegin.metadata, &rbegin, &rend))
	{
		int compare = lbegin.value_type_metadata.compare(
				lbegin.value_type_metadata,
				lbegin.metadata.dereference(&lbegin),
				rbegin.metadata.dereference(&rbegin));
		if (compare < 0)
			return true;
		else if (compare)
			return false;
		lbegin.metadata.increment(&lbegin);
		rbegin.metadata.increment(&rbegin);
	}
	return (lbegin.metadata.compare(lbegin.metadata, &lbegin, &lend) &&
			!rbegin.metadata.compare(rbegin.metadata, &rbegin, &rend));
}

int	ft_lexicographical_compare_three_way(iterator lbegin, iterator lend, iterator rbegin, iterator rend)
{
	while (lbegin.metadata.compare(lbegin.metadata, &lbegin, &lend) &&
		   rbegin.metadata.compare(rbegin.metadata, &rbegin, &rend))
	{
		int compare = lbegin.value_type_metadata.compare(
				lbegin.value_type_metadata,
				lbegin.metadata.dereference(&lbegin),
				rbegin.metadata.dereference(&rbegin));
		if (compare < 0)
			return -1;
		else if (compare)
			return 1;
		lbegin.metadata.increment(&lbegin);
		rbegin.metadata.increment(&rbegin);
	}
	if (lbegin.metadata.compare(lbegin.metadata, &lbegin, &lend))
		return 1;
	else if (rbegin.metadata.compare(rbegin.metadata, &rbegin, &rend))
		return -1;
	else
		return 0;
}