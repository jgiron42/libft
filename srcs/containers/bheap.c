#include "containers.h"

#define BHEAP_PARENT(i) (((i) - 1) / 2)
#define BHEAP_LEFT(i) (((i) + 1) * 2)
#define BHEAP_RIGHT(i) (((i) + 1) * 2 - 1)

status ft_bheap(type_metadata m, void *dst)
{
	status ret = ft_vector(m, dst);
	if (ret != OK)
		return ret;
	((container*)dst)->type = FT_BHEAP;
	((container*)dst)->metadata = meta[FT_BHEAP];
	return OK;
}

data_type ft_bheap_top(container *this)
{
	return ft_vector_front(this);
}

void	bheap_swap(container *this, int a, int b)
{
	char	tmp[this->value_type_metadata.size];
	this->value_type_metadata.assign(this->value_type_metadata, tmp, ft_vector_at_ptr(this, a));
	this->value_type_metadata.assign(this->value_type_metadata, ft_vector_at_ptr(this, a), ft_vector_at_ptr(this, b));
	this->value_type_metadata.assign(this->value_type_metadata, ft_vector_at_ptr(this, b), tmp);
}

status	ft_bheap_push_ptr(container *this, data_type *data)
{
	if (ft_vector_push_back_ptr(this,data) != OK)
		return FATAL;
	if (this->size > 1) {
		for (size_t i = this->size - 1; i > 0;) {
			register int parent = BHEAP_PARENT(i);
			if (this->value_type_metadata.compare(this->value_type_metadata, ft_vector_at_ptr(this, i),
												  ft_vector_at_ptr(this, parent)) < 0) // if val[i] > val[parent]
				bheap_swap(this, i, parent);
			else
				break;
			i = parent;
		}
	}
	return OK;
}

status	ft_bheap_push(container *this, data_type data)
{
	return ft_bheap_push_ptr(this, &data);
}

void	ft_bheap_pop(container *this)
{
	size_t i = 0;
	this->value_type_metadata.destructor(this->value_type_metadata, this->vector.data);
	this->value_type_metadata.assign(this->value_type_metadata, ft_vector_at_ptr(this, 0), ft_vector_at_ptr(this, this->size - 1));
	this->size--;
	while (1)
	{
		register size_t max = i;
		if (BHEAP_RIGHT(i) < this->size && this->value_type_metadata.compare(this->value_type_metadata, ft_vector_at_ptr(this, BHEAP_RIGHT(i)),
																				   ft_vector_at_ptr(this, i)) < 0) // right > current
			max = BHEAP_RIGHT(i);
		if (BHEAP_RIGHT(i) < this->size && this->value_type_metadata.compare(this->value_type_metadata, ft_vector_at_ptr(this, BHEAP_LEFT(i)), ft_vector_at_ptr(this, max)) < 0) // left > max(current, right)
			max = BHEAP_LEFT(i);
		if (max == i)
			break;
		bheap_swap(this, max, i);
		i = max;
	}
}