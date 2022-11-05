#ifndef GREP_ALGORITHMS_H
#define GREP_ALGORITHMS_H
#include "../containers/containers.h"
status	heap_sort(container *c);
bool		ft_lexicographical_compare(iterator lbegin, iterator lend, iterator rbegin, iterator rend);
int			ft_lexicographical_compare_three_way(iterator lbegin, iterator lend, iterator rbegin, iterator rend);
#endif //GREP_ALGORITHMS_H
