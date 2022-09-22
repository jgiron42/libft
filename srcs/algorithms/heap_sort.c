#include "algorithms.h"

status	heap_sort(container *c)
{
	container heap;
	if (ft_bheap(c->value_type_metadata, &heap) != OK)
		return FATAL;
	for_in(it, *c)
		if (ft_bheap_push(&heap, it.metadata.dereference(&it)) != OK)
		{
			heap.destroy(&heap);
			return FATAL;
		}
	c->clear(c);
	while (heap.size) {
		if (ft_vector_push_back(c, ft_bheap_top(&heap)) != OK) // TODO generic
		{
			heap.destroy(&heap);
			return FATAL;
		}
		ft_bheap_pop(&heap);
	}
	heap.destroy(&heap);
	return OK;
}