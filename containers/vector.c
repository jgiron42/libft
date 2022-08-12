#include "containers.h"

status ft_vector_default(type_metadata metadata, void *dst)
{
	(void)metadata;
	*(container *)dst = (container){
		.type = FT_VECTOR,
		.size = 0,
		.vector = {
				.data = NULL,
				.capacity = 0,
		}
	};
	return OK;
}

status ft_vector(type_metadata meta, void *dst)
{
	*(container *)dst = (container){
		.type = FT_VECTOR,
		.value_type_metadata = meta,
		.size = 0,
		.vector = {
				.data = NULL,
				.capacity = 0,
		}
	};
	return OK;
}

status ft_vector_copy(struct s_type_metadata meta, void *dst, const void *src)
{
	(void)meta;
	*(container *)dst = *(container *)src;
	(*(container *)dst).vector.data = malloc(((container *)dst)->size * sizeof(data_type));
	if (!(*(container *)dst).vector.data)
		return FATAL;
	memcpy((*(container *)dst).vector.data, (*(container *)src).vector.data, (*(container *)dst).size * sizeof(data_type));
	return OK;
}

void	ft_vector_clear(container *this)
{
	if (this->size)
	{
		for (size_t i = 0; i < this->size; i++)
			this->value_type_metadata.destructor(this->value_type_metadata, this->vector.data + i);
		this->size = 0;
	}
}

void	ft_vector_destructor(container *this)
{
	ft_vector_clear(this);
	if (this->vector.data)
		free(this->vector.data);
	this->vector.data = NULL;
	this->vector.capacity = 0;
}

iterator ft_vector_begin(container *this)
{
	return (iterator){
		.iterator_tag = FT_RANDOM_ACCESS_ITERATOR,
		.value_type_metadata = this->value_type_metadata,
		.metadata = FT_VECTOR_ITERATOR,
		.vector = {
				.current = this->vector.data,
		},
	};
}

iterator ft_vector_end(container *this)
{
	return (iterator){
		.iterator_tag = FT_RANDOM_ACCESS_ITERATOR,
		.value_type_metadata = this->value_type_metadata,
		.metadata = FT_VECTOR_ITERATOR,
		.vector = {
				.current = this->vector.data + this->size,
		},
	};
}

status	ft_vector_expand(container *dst, size_t count_more)
{
	size_t new_cap;

	if (dst->size + count_more < 2 * dst->vector.capacity)
		new_cap = 2 * dst->vector.capacity;
	else
		new_cap = dst->vector.capacity + count_more;

	data_type *new_ptr = malloc(new_cap * sizeof(data_type));
	if (!new_ptr)
		return (FATAL);
	for (size_t i = 0; i < dst->size; i++)
	{
		int ret;
		if ((ret = dst->value_type_metadata.copy(dst->value_type_metadata, new_ptr + i, dst->vector.data + i)) != OK)
		{
			free(new_ptr);
			return ret;
		}
	}
	dst->vector.capacity = new_cap;
	free(dst->vector.data);
	dst->vector.data = new_ptr;
	return (OK);
}

status	ft_vector_insert_val(container *this, iterator pos, data_type val)
{
	size_t offset = pos.vector.current - this->vector.data;
	if (this->vector.capacity < 1 + this->size && ft_vector_expand(this, 1) == FATAL)
		return FATAL;
	if (this->size > offset)
		ft_memmove(this->vector.data + offset + 1, this->vector.data + offset, (this->size - offset) * sizeof(data_type));
	this->size++;
	return this->value_type_metadata.copy(this->value_type_metadata, this->vector.data + offset, &val);
}

status	ft_vector_insert_range(container *this, iterator pos, iterator begin, iterator end)
{
	status ret;
	size_t offset = pos.vector.current - this->vector.data;
	if (begin.iterator_tag < FT_FORWARD_ITERATOR) // no multipass :(
	{
		while (begin.metadata.compare(begin.metadata ,&begin, &end))
		{
			data_type tmp;
			if ((ret = begin.value_type_metadata.copy(begin.value_type_metadata, &tmp, begin.metadata.dereference(&begin))) != OK)
				return ret;
			pos.vector.current = this->vector.data + offset;
			if ((ret = ft_vector_insert_val(this, pos, tmp)) != OK)
				return ret;
			offset--;
			begin.metadata.increment(&begin);
			this->size++;
		}
	}
	else // MULTIPASS!!!
	{
		size_t total = distance(begin, end);
		if (this->vector.capacity - this->size < total && ft_vector_expand(this, total) != OK)
			return FATAL;
		ft_memmove((this->vector.data + offset + total), this->vector.data + offset, (this->size - offset) * sizeof(data_type));
		for (size_t i = 0; i < total; i++, begin.metadata.increment(&begin))
		{
			void *value = begin.metadata.dereference(&begin);
			if ((ret = begin.value_type_metadata.copy(begin.value_type_metadata, this->vector.data + offset + i, &value)) != OK)
				return ret;
		}
		this->size += total;
	}
	return (OK);
}

iterator	ft_vector_erase_range(container *this, iterator begin, iterator end)
{
	data_type *tmp = begin.vector.current;
	while (tmp != end.vector.current)
	{
		this->value_type_metadata.destructor(this->value_type_metadata, tmp);
		tmp++;
	}
	if (this->vector.data + this->size - end.vector.current > 0)
		ft_memmove(begin.vector.current, end.vector.current, (this->vector.data + this->size - end.vector.current) * sizeof(data_type));
	this->size -= end.vector.current - begin.vector.current;
	return end;
}

iterator	ft_vector_erase_one(container *this, iterator it)
{
	iterator it2 = it;
	it2.vector.current++;
	return ft_vector_erase_range(this, it, it2);
}


status ft_vector_push_back(container *this, data_type data)
{
	return ft_vector_insert_val(this, ft_vector_end(this), data);
}

status ft_vector_push_front(container *this, data_type data)
{
	return ft_vector_insert_val(this, ft_vector_begin(this), data);
}

void ft_vector_pop_back(container *this)
{
	iterator it = ft_vector_end(this);
	it.vector.current--;
	ft_vector_erase_one(this, it);
}

void ft_vector_pop_front(container *this)
{
	ft_vector_erase_one(this, ft_vector_begin(this));
}

int	ft_vector_iterator_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;
	if (((iterator *)l)->vector.current < ((iterator *)r)->vector.current)
		return -1;
	else if (((iterator *)l)->vector.current > ((iterator *)r)->vector.current)
		return 1;
	return 0;
}

data_type ft_vector_iterator_dereference(void *it)
{
	return *(((iterator *)it)->vector.current);
}

void *ft_vector_iterator_increment(void *it)
{
	((iterator *)it)->vector.current++;
	return it;
}

void *ft_vector_iterator_decrement(void *it)
{
	((iterator *)it)->vector.current--;
	return it;
}

void *ft_vector_iterator_add(void *it, ssize_t to_add)
{
	((iterator *)it)->vector.current += to_add;
	return it;
}

ssize_t	ft_vector_iterator_diff(void *l, void *r)
{
	return ((iterator *)r)->vector.current - ((iterator *)l)->vector.current;
}