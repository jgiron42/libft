#include "containers.h"

status ft_bheap(type_metadata meta, void *dst)
{
	status ret = ft_vector(meta, dst);
	if (ret == OK)
		((container*)dst)->type = FT_BHEAP;
	return OK;
}

data_type ft_bheap_min(container *this)
{
	return ft_vector_front(this);
}

status	ft_bheap_insert(container *this, data_type data)
{
	ft_vector_push_back(data);

}