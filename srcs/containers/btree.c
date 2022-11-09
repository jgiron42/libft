#include "containers.h"
#include "includes/algorithms.h"
#include "ft_strings.h"

status ft_btree_default(type_metadata metadata, void *dst)
{
	(void)metadata;
	*(container *)dst = (container){
			.type = FT_BTREE,
			.init = true,
			.metadata = meta[FT_BTREE],
			.size = 0,
			.value_type_size = sizeof (data_type),
			.btree = {
					.past_the_end = {
							.parent = NULL,
							.left = NULL,
							.right = NULL,
					},
					.multi = false
			},
			.begin = &ft_btree_begin,
			.end = &ft_btree_end,
			.clear = &ft_btree_clear,
			.destroy = &ft_btree_destructor,
			.copy = &ft_btree_copy,
	};
	(*(container *)dst).btree.first = &(*(container *)dst).btree.past_the_end;
	(*(container *)dst).btree.last = &(*(container *)dst).btree.past_the_end;
	return OK;
}

status ft_btree(type_metadata value, void *dst)
{
	*(container *)dst = (container){
			.type = FT_BTREE,
			.init = true,
			.metadata = meta[FT_BTREE],
			.value_type_metadata = value,
			.size = 0,
			.value_type_size = sizeof (data_type),
			.btree = {
					.past_the_end = {
							.parent = NULL,
							.left = NULL,
							.right = NULL,
					},
					.multi = false
			},
			.begin = &ft_btree_begin,
			.end = &ft_btree_end,
			.clear = &ft_btree_clear,
			.destroy = &ft_btree_destructor,
			.copy = &ft_btree_copy,
	};
	(*(container *)dst).btree.first = &(*(container *)dst).btree.past_the_end;
	(*(container *)dst).btree.last = &(*(container *)dst).btree.past_the_end;
	return OK;
}

iterator ft_btree_begin(container *this)
{
	return (iterator){
		.iterator_tag = FT_BIDIRECTIONAL_ITERATOR,
		.metadata = FT_BTREE_ITERATOR,
		.value_type_metadata = this->value_type_metadata,
		.container_type = FT_BTREE,
		.btree = {
				.current = this->btree.first,
		}
	};
}

iterator ft_btree_end(container *this)
{
	return (iterator){
		.iterator_tag = FT_BIDIRECTIONAL_ITERATOR,
		.metadata = FT_BTREE_ITERATOR,
		.value_type_metadata = this->value_type_metadata,
		.container_type = FT_BTREE,
		.btree = {
				.current = &this->btree.past_the_end,
		},
	};
}

btree_node *deep_copy(container *this, const container *other, btree_node *n)
{
	btree_node *ret = malloc(sizeof(btree_node) - sizeof(data_type) + this->value_type_size);
	if (!ret)
		return NULL;
	*ret = *n;
	if ( this->value_type_metadata.copy(this->value_type_metadata, &ret->data, &n->data) != OK)
		return NULL;
	if (ret->left)
	{
		btree_node *tmp = ret->left;
		ret->left = deep_copy(this, other, ret->left);
		if (!ret->left)
		{
			free(ret);
			return NULL;
		}
		if (tmp == other->btree.first)
			this->btree.first = ret->left;
		ret->left->parent = ret;
	}
	if (ret->right)
	{
		btree_node *tmp = ret->right;
		ret->right = deep_copy(this, other, ret->right);
		if (!ret->right)
		{
			free(ret);
			return NULL;
		}
		if (tmp == other->btree.last)
			this->btree.last = ret->right;
		ret->right->parent = ret;
	}
	return ret;
}

status ft_btree_copy(struct s_type_metadata meta, void *dst, const void *src)
{
	(void)meta;
	(*(container*)dst) = (*(container*)src);
	if (((container *)dst)->btree.past_the_end.left)
	{
		((container *)dst)->btree.past_the_end.left = deep_copy(dst, src, ((container *)dst)->btree.past_the_end.left);
		if (!((container *)dst)->btree.past_the_end.left)
			return FATAL;
		((container *)dst)->btree.past_the_end.right = ((container *)dst)->btree.past_the_end.left;
		((container *)dst)->btree.past_the_end.right->parent = &((container *)dst)->btree.past_the_end;
		if (((container *)src)->btree.past_the_end.right == ((container *)src)->btree.first)
			((container *)dst)->btree.first = ((container *)dst)->btree.past_the_end.right;
		if (((container *)src)->btree.past_the_end.right == ((container *)src)->btree.last)
			((container *)dst)->btree.last = ((container *)dst)->btree.past_the_end.right;
	}
	return OK;
}

int		ft_btree_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;
	return ft_lexicographical_compare_three_way(
		(*(container*)l).begin(((container*)l)), (*(container*)l).end(((container*)l)),
		(*(container*)r).begin(((container*)r)), (*(container*)r).end(((container*)r))
		);
}

void	deep_clear(container *this, btree_node *n)
{
	if (n->right)
	{
		deep_clear(this, n->right);
		n->right = NULL;
	}
	if (n->left)
	{
		deep_clear(this, n->left);
		n->left = NULL;
	}
	this->value_type_metadata.destructor(this->value_type_metadata, &n->data);
	free(n);
}

void	ft_btree_clear(container *this)
{
	if (this->btree.past_the_end.right)
		deep_clear(this, this->btree.past_the_end.right);
	this->btree.first = &this->btree.past_the_end;
	this->btree.last = &this->btree.past_the_end;
	this->btree.past_the_end.left = NULL;
	this->btree.past_the_end.right = NULL;
	this->size = 0;
}

void	ft_btree_destructor(container *this)
{
	ft_btree_clear(this);
}

void	ft_btree_destructor_wrapper(type_metadata meta, void *container)
{
	(void)meta;
	ft_btree_destructor(container);
}

iterator	ft_btree_find_recurse(container *this, btree_node *current, data_type key)
{
	if (!current)
		return (ft_btree_end(this));
	int tmp = this->value_type_metadata.compare(this->value_type_metadata, &key, &current->data);
	if (tmp < 0)
		return ft_btree_find_recurse(this, current->left, key);
	else if (tmp > 0)
		return ft_btree_find_recurse(this, current->right, key);
	else
	{
		iterator ret = ft_btree_begin(this);
		ret.btree.current = current;
		return ret;
	}
}

iterator	ft_btree_find(container *this, data_type key)
{
	return ft_btree_find_recurse(this, this->btree.past_the_end.left, key);
}

iterator	ft_btree_insert_recurse(container *this, btree_node *current, data_type value)
{
	btree_node **dst;
	int tmp = this->value_type_metadata.compare(this->value_type_metadata, value, &current->data);
	if (tmp < 0)
	{
		if (current->left)
			return ft_btree_insert_recurse(this, current->left, value);
		dst = &current->left;
	}
	else if (tmp > 0 || (this->btree.multi && tmp == 0))
	{
		if (current->right)
			return ft_btree_insert_recurse(this, current->right, value);
		dst = &current->right;
	}
	else
	{
		iterator ret = ft_btree_begin(this);
		ret.btree.current = current;
		return ret;
	}
	*dst = malloc(sizeof(btree_node) - sizeof(data_type) + this->value_type_size);
	if (!*dst)
		return (ft_btree_end(this));
	ft_bzero(*dst, sizeof(btree_node) - sizeof(data_type) + this->value_type_size);
	if (this->value_type_metadata.copy(this->value_type_metadata, &(*dst)->data, value) != OK)
		return (ft_btree_end(this));
	(*dst)->parent = current;
	if (this->btree.first == current && dst == &current->left)
		this->btree.first = *dst;
	if (this->btree.last == current && dst == &current->right)
		this->btree.last = *dst;
	this->size++;
	iterator ret = ft_btree_begin(this);
	ret.btree.current = *dst;
	return ret;
}

// find or insert the value or object pointed by ptr, if an error occur end is returned otherwise the iterator to the inserted value
iterator	ft_btree_insert_ptr(container *this, data_type *val)
{
	if (this->size == 0)
	{
		btree_node * new_node = malloc(sizeof(btree_node) - sizeof(data_type) + this->value_type_size);
		if (!new_node)
			return (ft_btree_end(this));
		ft_bzero(new_node, sizeof(btree_node) - sizeof(data_type) + this->value_type_size);
		if (this->value_type_metadata.copy(this->value_type_metadata, &new_node->data, val) != OK)
		{
			free(new_node);
			return (ft_btree_end(this));
		}
		new_node->parent = &this->btree.past_the_end;
		this->btree.past_the_end.left = new_node;
		this->btree.past_the_end.right = new_node;
		this->btree.first = new_node;
		this->btree.last = new_node;
		this->size++;
		iterator ret = ft_btree_begin(this);
		ret.btree.current = new_node;
		return ret;
	}
	return ft_btree_insert_recurse(this, this->btree.past_the_end.left, val);
}

// find or insert an atomic value, if an error occur end is returned otherwise the iterator to the inserted value
iterator	ft_btree_insert_val(container *this, data_type val)
{
	return ft_btree_insert_ptr(this, &val);
}

status		ft_btree_insert_range(container *this, iterator begin, iterator end) {
	iterator this_end = ft_btree_end(this);
	while (begin.metadata.compare(begin.metadata, &begin, &end))
	{
		iterator tmp = ft_btree_insert_ptr(this, begin.metadata.reference(&begin));
		if (!tmp.metadata.compare(tmp.metadata, &tmp, &this_end))
			return FATAL;
		begin.metadata.increment(&begin);
	}
	return OK;
}

iterator ft_btree_erase_one(container *this, iterator it)
{
	btree_node *n = it.btree.current;
	btree_node **nptr = n->parent->left == n ? &n->parent->left : &n->parent->right;
	iterator ret = it;
	ft_btree_iterator_increment(&ret);
	if (n->left && n->right)
	{
		btree_node *tmp = n->left;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = n->right;
		n->right->parent = tmp;
		*nptr = n->left;
		n->left->parent = n->parent;
	}
	else if (n->left)
	{
		*nptr = n->left;
		if (n->left)
			n->left->parent = n->parent;
	}
	else if (n->right)
	{
		*nptr = n->right;
		if (n->right)
			n->right->parent = n->parent;
	}
	else
		*nptr = NULL;
	if (nptr == &this->btree.past_the_end.left)
		this->btree.past_the_end.right = this->btree.past_the_end.left;
	if (n == this->btree.last)
	{
		if (*nptr)
			this->btree.last = *nptr;
		else
			this->btree.last = n->parent;
	}
	if (n == this->btree.first)
	{
		if (*nptr)
			this->btree.first = *nptr;
		else
			this->btree.first = n->parent;
	}
	this->value_type_metadata.destructor(this->value_type_metadata, &n->data);
	free(n);
	this->size--;
	return ret;
}

int	ft_btree_iterator_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;
	return (((iterator *)l)->btree.current != ((iterator *)r)->btree.current);
}

data_type ft_btree_iterator_dereference(void *it)
{
	return (((iterator *)it)->btree
			.current->data);
}

data_type *ft_btree_iterator_reference(void *it)
{
	return (&((iterator *)it)->btree
			.current->data);
}

void *ft_btree_iterator_increment(void *it)
{
	if (((iterator *)it)->btree.current->right)
	{
		((iterator *)it)->btree.current = ((iterator *)it)->btree.current->right;
		while (((iterator *)it)->btree.current->left)
			((iterator *)it)->btree.current = ((iterator *)it)->btree.current->left;
	}
	else if (((iterator *)it)->btree.current->parent->left == ((iterator *)it)->btree.current)
		((iterator *)it)->btree.current = ((iterator *)it)->btree.current->parent;
	else
	{
		while (((iterator *)it)->btree.current->parent && ((iterator *)it)->btree.current->parent->left != ((iterator *)it)->btree.current)
			((iterator *)it)->btree.current = ((iterator *)it)->btree.current->parent;
		if (((iterator *)it)->btree.current->parent)
			((iterator *)it)->btree.current = ((iterator *)it)->btree.current->parent;
	}
	return it;
}

void *ft_btree_iterator_decrement(void *it)
{
	if (((iterator *)it)->btree.current->left)
	{
		((iterator *)it)->btree.current = ((iterator *)it)->btree.current->left;
		while (((iterator *)it)->btree.current->right)
			((iterator *)it)->btree.current = ((iterator *)it)->btree.current->right;
	}
	else if (((iterator *)it)->btree.current->parent->right == ((iterator *)it)->btree.current)
		((iterator *)it)->btree.current = ((iterator *)it)->btree.current->parent;
	else
	{
		while (((iterator *)it)->btree.current->parent && ((iterator *)it)->btree.current->parent->right != ((iterator *)it)->btree.current)
			((iterator *)it)->btree.current = ((iterator *)it)->btree.current->parent;
		if (((iterator *)it)->btree.current->parent)
			((iterator *)it)->btree.current = ((iterator *)it)->btree.current->parent;
	}
	return it;
}
