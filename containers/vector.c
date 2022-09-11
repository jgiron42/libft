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
				.align = sizeof(data_type),
		},
		.begin = &ft_vector_begin,
		.end = &ft_vector_end,
		.clear = &ft_vector_clear,
		.destroy = &ft_vector_destructor,
		.copy = &ft_vector_copy,
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
				.align = sizeof(data_type),
		},
		.begin = &ft_vector_begin,
		.end = &ft_vector_end,
		.clear = &ft_vector_clear,
		.destroy = &ft_vector_destructor,
		.copy = &ft_vector_copy,
	};
	return OK;
}

status ft_vector_copy(struct s_type_metadata meta, void *dst, const void *src)
{
	(void)meta;
	*(container *)dst = *(container *)src;
	(*(container *)dst).vector.data = malloc(((container *)dst)->size * (*(container *)src).vector.align);
	if (!(*(container *)dst).vector.data)
		return FATAL;
	memcpy((*(container *)dst).vector.data, (*(container *)src).vector.data, (*(container *)dst).size * (*(container *)src).vector.align);
	return OK;
}

void	ft_vector_clear(container *this)
{
	if (this->size)
	{
		for (size_t i = 0; i < this->size; i++)
			this->value_type_metadata.destructor(this->value_type_metadata, this->vector.data + i * this->vector.align);
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
				.align = this->vector.align,
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
				.current = this->vector.data + this->size * this->vector.align,
				.align = this->vector.align,
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

	char *new_ptr = malloc(new_cap * dst->vector.align);
	if (!new_ptr)
		return (FATAL);
	for (size_t i = 0; i < dst->size; i++)
	{
		int ret;
		if ((ret = dst->value_type_metadata.copy(dst->value_type_metadata, new_ptr + i * dst->vector.align, dst->vector.data + i * dst->vector.align)) != OK)
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
	if (this->size * this->vector.align > offset)
		ft_memmove(this->vector.data + offset + this->vector.align, this->vector.data + offset, (this->size - offset) * this->vector.align);
	this->size++;
	return this->value_type_metadata.copy(this->value_type_metadata, this->vector.data + offset, &val);
}

status	ft_vector_insert_range(container *this, iterator pos, iterator begin, iterator end)
{
	status ret;
	size_t offset = (pos.vector.current - this->vector.data) / this->vector.align;
	if (begin.iterator_tag < FT_FORWARD_ITERATOR) // no multipass :(
	{
		while (begin.metadata.compare(begin.metadata ,&begin, &end))
		{
			data_type tmp;
			if ((ret = begin.value_type_metadata.copy(begin.value_type_metadata, &tmp, begin.metadata.dereference(&begin))) != OK)
				return ret;
			pos.vector.current = this->vector.data + offset * this->vector.align;
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
		ft_memmove((this->vector.data + (offset + total) * this->vector.align), this->vector.data + offset * this->vector.align, (this->size - offset) * this->vector.align);
		for (size_t i = 0; i < total; i++, begin.metadata.increment(&begin))
		{
			void *value = begin.metadata.dereference(&begin);
			if ((ret = begin.value_type_metadata.copy(begin.value_type_metadata, this->vector.data + (offset + i) * this->vector.align, &value)) != OK)
				return ret;
		}
		this->size += total;
	}
	return (OK);
}

status	ft_vector_insert_count(container *this, iterator pos, data_type val, size_t count)
{
	status ret;
	size_t offset = (pos.vector.current - this->vector.data) / this->vector.align;
	if (this->vector.capacity - this->size < count && ft_vector_expand(this, count) != OK)
		return FATAL;
	ft_memmove((this->vector.data + (offset + count) * this->vector.align), this->vector.data + offset * this->vector.align, (this->size - offset) * this->vector.align);
	for (size_t i = 0; i < count; i++)
		if ((ret = pos.value_type_metadata.copy(pos.value_type_metadata, this->vector.data + (offset + i) * this->vector.align, &val)) != OK)
			return ret;
	this->size += count;
	return (OK);
}

iterator	ft_vector_erase_range(container *this, iterator begin, iterator end)
{
	char *tmp = begin.vector.current;
	while (tmp != end.vector.current)
	{
		this->value_type_metadata.destructor(this->value_type_metadata, tmp);
		tmp += this->vector.align;
	}
	if (this->vector.data + this->size * this->vector.align - end.vector.current > 0)
		ft_memmove(begin.vector.current, end.vector.current, (this->vector.data + this->size * this->vector.align - end.vector.current));
	this->size -= (end.vector.current - begin.vector.current) / this->vector.align;
	return end;
}

iterator	ft_vector_erase_one(container *this, iterator it)
{
	iterator it2 = it;
	it2.vector.current += this->vector.align;
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
	it.vector.current -= this->vector.align;
	ft_vector_erase_one(this, it);
}

void ft_vector_pop_front(container *this)
{
	ft_vector_erase_one(this, ft_vector_begin(this));
}

data_type ft_vector_at(const container *this, size_t pos)
{
	switch (this->vector.align)
	{
		case 1:
			return (data_type)(uint64_t)*((uint8_t *)(this->vector.data + this->vector.align * pos));
		case 2:
			return (data_type)(uint64_t)*((uint16_t *)(this->vector.data + this->vector.align * pos));
		case 4:
			return (data_type)(uint64_t)*((uint32_t *)(this->vector.data + this->vector.align * pos));
		case 8:
			return (data_type)(uint64_t)*((uint64_t *)(this->vector.data + this->vector.align * pos));
		default:
			return 0;
	}
}
data_type ft_vector_back(container *this)
{
	return ft_vector_at(this, this->size - 1);
}

data_type ft_vector_front(container *this)
{
	return ft_vector_at(this, 0);
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
	switch (((iterator*)it)->vector.align)
	{
		case 1:
			return (data_type)(uint64_t)*((uint8_t *)(((iterator *)it)->vector.current));
		case 2:
			return (data_type)(uint64_t)*((uint16_t *)(((iterator *)it)->vector.current));
		case 4:
			return (data_type)(uint64_t)*((uint32_t *)(((iterator *)it)->vector.current));
		case 8:
			return (data_type)(uint64_t)*((uint64_t *)(((iterator *)it)->vector.current));
		default:
			return 0;
	}
}

void *ft_vector_iterator_increment(void *it)
{
	((iterator *)it)->vector.current += ((iterator *)it)->vector.align;
	return it;
}

void *ft_vector_iterator_decrement(void *it)
{
	((iterator *)it)->vector.current -=	((iterator *)it)->vector.align;
	return it;
}

void *ft_vector_iterator_add(void *it, ssize_t to_add)
{
	((iterator *)it)->vector.current += to_add * ((iterator *)it)->vector.align;
	return it;
}

ssize_t	ft_vector_iterator_diff(void *l, void *r)
{
	return (((iterator *)r)->vector.current - ((iterator *)l)->vector.current) / ((iterator *)l)->vector.align;
}