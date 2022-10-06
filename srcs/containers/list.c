#include "containers.h"

status ft_list_default(type_metadata metadata, void *dst)
{
	(void)metadata;
	*(container *)dst = (container){
			.metadata = meta[FT_LIST],
			.type = FT_LIST,
			.size = 0,
			.list = {
					.past_the_end = {
							.next = NULL,
							.prev = NULL,
					},
			},
			.begin = &ft_list_begin,
			.end = &ft_list_end,
			.clear = &ft_list_clear,
			.destroy = &ft_list_destructor,
			.copy = &ft_list_copy,
	};
	return OK;
}

status ft_list(type_metadata m, void *dst)
{
	*(container *)dst = (container){
			.type = FT_LIST,
			.metadata = meta[FT_LIST],
			.value_type_metadata = m,
			.size = 0,
			.list = {
					.past_the_end = {
						.next = NULL,
						.prev = NULL,
					},
			},
			.begin = &ft_list_begin,
			.end = &ft_list_end,
			.clear = &ft_list_clear,
			.destroy = &ft_list_destructor,
			.copy = &ft_list_copy,
	};
	return OK;
}

status ft_list_copy(struct s_type_metadata meta, void *dst, const void *src)
{
	(void)meta;
	ft_list(((container *)src)->value_type_metadata, dst);
	ft_list_insert_range(dst,ft_list_begin((container *)dst), ft_list_begin((container *)src), ft_list_end((container *)src));
	return OK;
}



void	ft_list_destructor(container *this)
{
	ft_list_clear(this);
}

void	ft_list_destructor_wrapper(type_metadata meta, void *container)
{
	(void)meta;
	ft_list_destructor(container);
}


iterator ft_list_begin(container *this)
{
	return (iterator){
			.iterator_tag = FT_BIDIRECTIONAL_ITERATOR,
			.value_type_metadata = this->value_type_metadata,
			.metadata = FT_LIST_ITERATOR,
			.list = {
					.current = this->list.past_the_end.next,
			},
	};
}

iterator ft_list_end(container *this)
{
	return (iterator){
			.iterator_tag = FT_BIDIRECTIONAL_ITERATOR,
			.value_type_metadata = this->value_type_metadata,
			.metadata = FT_LIST_ITERATOR,
			.list = {
					.current = &this->list.past_the_end,
			},
	};
}

void	ft_list_clear(container *this)
{
	ft_list_erase_range(this, ft_list_begin(this), ft_list_end(this));
}

status	ft_list_insert_val(container *this, iterator pos, data_type val)
{
	list_node *node = malloc(sizeof(list_node));
	if (!node)
		return FATAL;
	*node = (list_node){};
	status ret;
	if ((ret = this->value_type_metadata.copy(this->value_type_metadata, &node->data, &val)) != OK)
	{
		free(node);
		return ret;
	}

	if (!this->list.past_the_end.prev)
	{
		this->list.past_the_end.prev = node;
		this->list.past_the_end.next = node;
		node->next = &this->list.past_the_end;
		node->prev = &this->list.past_the_end;
	}
	else {
		node->prev = pos.list.current->prev;
		node->next = pos.list.current;
		if (pos.list.current->prev)
			pos.list.current->prev->next = node;
		pos.list.current->prev = node;
	}
	this->size++;
	return (OK);
}

status	ft_list_insert_range(container *this, iterator pos, iterator begin, iterator end)
{
	while (begin.metadata.compare(begin.metadata, &begin, &end))
	{
		status ret;
		if ((ret = ft_list_insert_val(this, pos, begin.metadata.dereference(&begin))) != OK)
			return ret;
		begin.metadata.increment(&begin);
	}
	return OK;
}

iterator	ft_list_erase_one(container *this, iterator it)
{
	if (!it.list.current->next)
	{
		this->list.past_the_end.prev = it.list.current->prev;
		it.list.current->next = &this->list.past_the_end;
	}
	else
		it.list.current->next->prev = it.list.current->prev;
	if (!it.list.current->prev)
	{
		this->list.past_the_end.next = it.list.current->next;
		it.list.current->prev = &this->list.past_the_end;
	}
	else
		it.list.current->prev->next = it.list.current->next;
	it.value_type_metadata.destructor(it.value_type_metadata, &it.list.current->data);
	list_node *ret = it.list.current->next;
	free(it.list.current);
	it.list.current = ret;
	this->size--;
	return it;
}

iterator	ft_list_erase_range(container *this, iterator begin, iterator end)
{
	while (begin.metadata.compare(begin.metadata, &begin, &end))
		begin = ft_list_erase_one(this, begin);
	return begin;
}

data_type	*ft_list_front(container *this)
{
	if (this->size)
		return &this->list.past_the_end.next->data;
	return NULL;
}

data_type	*ft_list_back(container *this)
{
	if (this->size)
		return &this->list.past_the_end.prev->data;
	return NULL;
}

int	ft_list_iterator_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;
	return (((iterator *)l)->list.current != ((iterator *)r)->list.current);
}

data_type ft_list_iterator_dereference(void *it)
{
	return ((iterator *)it)->list.current->data;
}

void *ft_list_iterator_increment(void *it)
{
	if (((iterator *)it)->list.current)
		((iterator *)it)->list.current = ((iterator *)it)->list.current->next;
	return it;
}

void *ft_list_iterator_decrement(void *it)
{
	if (((iterator *)it)->list.current)
		((iterator *)it)->list.current = ((iterator *)it)->list.current->prev;
	return it;
}