#include "containers.h"
#include "includes/algorithms.h"
#include "ft_strings.h"

status ft_bst_default(type_metadata metadata, void *dst)
{
	(void)metadata;
	*(container *)dst = (container){
			.type = FT_BST,
			.init = true,
			.metadata = meta[FT_BST],
			.size = 0,
			.value_type_size = sizeof (data_type),
			.bst = {
					.past_the_end = {
							.parent = NULL,
							.left = NULL,
							.right = NULL,
					},
					.multi = false
			},
			.begin = &ft_bst_begin,
			.end = &ft_bst_end,
			.clear = &ft_bst_clear,
			.destroy = &ft_bst_destructor,
			.copy = &ft_bst_copy,
	};
	(*(container *)dst).bst.first = &(*(container *)dst).bst.past_the_end;
	(*(container *)dst).bst.last = &(*(container *)dst).bst.past_the_end;
	return OK;
}

status ft_bst(type_metadata value, void *dst)
{
	*(container *)dst = (container){
			.type = FT_BST,
			.init = true,
			.metadata = meta[FT_BST],
			.value_type_metadata = value,
			.size = 0,
			.value_type_size = sizeof (data_type),
			.bst = {
					.past_the_end = {
							.parent = NULL,
							.left = NULL,
							.right = NULL,
					},
					.multi = false
			},
			.begin = &ft_bst_begin,
			.end = &ft_bst_end,
			.clear = &ft_bst_clear,
			.destroy = &ft_bst_destructor,
			.copy = &ft_bst_copy,
	};
	(*(container *)dst).bst.first = &(*(container *)dst).bst.past_the_end;
	(*(container *)dst).bst.last = &(*(container *)dst).bst.past_the_end;
	return OK;
}

iterator ft_bst_begin(container *this)
{
	return (iterator){
		.iterator_tag = FT_BIDIRECTIONAL_ITERATOR,
		.metadata = FT_BST_ITERATOR,
		.value_type_metadata = this->value_type_metadata,
		.container_type = FT_BST,
		.bst = {
				.current = this->bst.first,
		}
	};
}

iterator ft_bst_end(container *this)
{
	return (iterator){
		.iterator_tag = FT_BIDIRECTIONAL_ITERATOR,
		.metadata = FT_BST_ITERATOR,
		.value_type_metadata = this->value_type_metadata,
		.container_type = FT_BST,
		.bst = {
				.current = &this->bst.past_the_end,
		},
	};
}

bst_node *deep_copy(container *this, const container *other, bst_node *n)
{
	bst_node *ret = malloc(sizeof(bst_node) - sizeof(data_type) + this->value_type_size);
	if (!ret)
		return NULL;
	*ret = *n;
	if ( this->value_type_metadata.copy(this->value_type_metadata, &ret->data, &n->data) != OK)
		return NULL;
	if (ret->left)
	{
		bst_node *tmp = ret->left;
		ret->left = deep_copy(this, other, ret->left);
		if (!ret->left)
		{
			free(ret);
			return NULL;
		}
		if (tmp == other->bst.first)
			this->bst.first = ret->left;
		ret->left->parent = ret;
	}
	if (ret->right)
	{
		bst_node *tmp = ret->right;
		ret->right = deep_copy(this, other, ret->right);
		if (!ret->right)
		{
			free(ret);
			return NULL;
		}
		if (tmp == other->bst.last)
			this->bst.last = ret->right;
		ret->right->parent = ret;
	}
	return ret;
}

status ft_bst_copy(struct s_type_metadata meta, void *dst, const void *src)
{
	(void)meta;
	(*(container*)dst) = (*(container*)src);
	if (((container *)dst)->bst.past_the_end.left)
	{
		((container *)dst)->bst.past_the_end.left = deep_copy(dst, src, ((container *)dst)->bst.past_the_end.left);
		if (!((container *)dst)->bst.past_the_end.left)
			return FATAL;
		((container *)dst)->bst.past_the_end.right = ((container *)dst)->bst.past_the_end.left;
		((container *)dst)->bst.past_the_end.right->parent = &((container *)dst)->bst.past_the_end;
		if (((container *)src)->bst.past_the_end.right == ((container *)src)->bst.first)
			((container *)dst)->bst.first = ((container *)dst)->bst.past_the_end.right;
		if (((container *)src)->bst.past_the_end.right == ((container *)src)->bst.last)
			((container *)dst)->bst.last = ((container *)dst)->bst.past_the_end.right;
	}
	return OK;
}

int		ft_bst_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;
	return ft_lexicographical_compare_three_way(
		(*(container*)l).begin(((container*)l)), (*(container*)l).end(((container*)l)),
		(*(container*)r).begin(((container*)r)), (*(container*)r).end(((container*)r))
		);
}

void	deep_clear(container *this, bst_node *n)
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

void	ft_bst_clear(container *this)
{
	if (this->bst.past_the_end.right)
		deep_clear(this, this->bst.past_the_end.right);
	this->bst.first = &this->bst.past_the_end;
	this->bst.last = &this->bst.past_the_end;
	this->bst.past_the_end.left = NULL;
	this->bst.past_the_end.right = NULL;
	this->size = 0;
}

void	ft_bst_destructor(container *this)
{
	ft_bst_clear(this);
}

void	ft_bst_destructor_wrapper(type_metadata meta, void *container)
{
	(void)meta;
	ft_bst_destructor(container);
}

bst_node	*ft_bst_rotate_right(bst_node *current)
{
	if (!current || !current->left)
		return current;
	bst_node *l = current->left;
	bst_node *p = current->parent;

	current->left = l->right;
	if (current->left)
		current->left->parent = current;
	l->right = current;
	if (l->right)
		l->right->parent = l->right;
	if (p->right == current)
		p->right = l;
	if (p->left == current)
		p->left = l;
	l->parent = p;
	return l;
}

bst_node	*ft_bst_rotate_left(bst_node *current)
{
	if (!current || !current->right)
		return current;
	bst_node *r = current->right;
	bst_node *p = current->parent;

	current->right = r->left;
	if (current->right)
		current->right->parent = current;
	r->left = current;
	if (r->left)
		r->left->parent = r->left;
	if (p->right == current)
		p->right = r;
	if (p->left == current)
		p->left = r;
	r->parent = p;
	return r;
}

iterator	ft_bst_find_recurse(container *this, bst_node *current, data_type key)
{
	if (!current)
		return (ft_bst_end(this));
	int tmp = this->value_type_metadata.compare(this->value_type_metadata, &key, &current->data);
	if (tmp < 0)
		return ft_bst_find_recurse(this, current->left, key);
	else if (tmp > 0)
		return ft_bst_find_recurse(this, current->right, key);
	else
	{
		iterator ret = ft_bst_begin(this);
		ret.bst.current = current;
		return ret;
	}
}

iterator	ft_bst_find(container *this, data_type key)
{
	return ft_bst_find_recurse(this, this->bst.past_the_end.left, key);
}

// action: +1 means add left or remove right, -1 means add right or remove left;
void		ft_bst_balance_avl(container *this, bst_node *current, char action)
{
	// if no node was added then the tree is already balanced
	if (!action)
		return;

	// if it happens that the added node balance the subtree then there is nothing to do
	if (!(current->balance_factor + action))
	{
		current->balance_factor = 0;
		return;
	}

	if (!current->balance_factor)
	{
		current->balance_factor = action;
		if (current->parent == &this->bst.past_the_end) // the whole tree has grown
			return;
		if (current->parent->right == current)
			ft_bst_balance_avl(this, current->parent, -1);
		else
			ft_bst_balance_avl(this, current->parent, +1);
	}
	else if (action == 1)
	{
		if (current->right && current->right->balance_factor == -1)
			ft_bst_rotate_right(current->right);
		ft_bst_rotate_left(current);
	}
	else // action == -1
	{
		if (current->left && current->left->balance_factor == 1)
			ft_bst_rotate_left(current->left);
		ft_bst_rotate_right(current);
	}
}

iterator	ft_bst_insert_recurse(container *this, bst_node *current, data_type value)
{
	bst_node **dst;
	int tmp = this->value_type_metadata.compare(this->value_type_metadata, value, &current->data);
	if (tmp < 0)
	{
		if (current->left)
			return ft_bst_insert_recurse(this, current->left, value);
		dst = &current->left;
	}
	else if (tmp > 0 || (this->bst.multi && tmp == 0))
	{
		if (current->right)
			return ft_bst_insert_recurse(this, current->right, value);
		dst = &current->right;
	}
	else
	{
		iterator ret = ft_bst_begin(this);
		ret.bst.current = current;
		return ret;
	}
	*dst = malloc(sizeof(bst_node) - sizeof(data_type) + this->value_type_size);
	if (!*dst)
		return (ft_bst_end(this));
	ft_bzero(*dst, sizeof(bst_node) - sizeof(data_type) + this->value_type_size);
	if (this->value_type_metadata.copy(this->value_type_metadata, &(*dst)->data, value) != OK)
		return (ft_bst_end(this));
	(*dst)->parent = current;
	if (this->bst.first == current && dst == &current->left)
		this->bst.first = *dst;
	if (this->bst.last == current && dst == &current->right)
		this->bst.last = *dst;
	this->size++;
	iterator ret = ft_bst_begin(this);
	ret.bst.current = *dst;
	if (this->bst.type == AVL)
	{
		if ((*dst)->parent->right == (*dst))
			ft_bst_balance_avl(this, (*dst)->parent, -1);
		else
			ft_bst_balance_avl(this, (*dst)->parent, +1);
	}
	return ret;
}

// find or insert the value or object pointed by ptr, if an error occur end is returned otherwise the iterator to the inserted value
iterator	ft_bst_insert_ptr(container *this, data_type *val)
{
	if (this->size == 0)
	{
		bst_node * new_node = malloc(sizeof(bst_node) - sizeof(data_type) + this->value_type_size);
		if (!new_node)
			return (ft_bst_end(this));
		ft_bzero(new_node, sizeof(bst_node) - sizeof(data_type) + this->value_type_size);
		if (this->value_type_metadata.copy(this->value_type_metadata, &new_node->data, val) != OK)
		{
			free(new_node);
			return (ft_bst_end(this));
		}
		new_node->parent = &this->bst.past_the_end;
		this->bst.past_the_end.left = new_node;
		this->bst.past_the_end.right = new_node;
		this->bst.first = new_node;
		this->bst.last = new_node;
		this->size++;
		iterator ret = ft_bst_begin(this);
		ret.bst.current = new_node;
		return ret;
	}
	return ft_bst_insert_recurse(this, this->bst.past_the_end.left, val);
}

// find or insert an atomic value, if an error occur end is returned otherwise the iterator to the inserted value
iterator	ft_bst_insert_val(container *this, data_type val)
{
	return ft_bst_insert_ptr(this, &val);
}

status		ft_bst_insert_range(container *this, iterator begin, iterator end) {
	iterator this_end = ft_bst_end(this);
	while (begin.metadata.compare(begin.metadata, &begin, &end))
	{
		iterator tmp = ft_bst_insert_ptr(this, begin.metadata.reference(&begin));
		if (!tmp.metadata.compare(tmp.metadata, &tmp, &this_end))
			return FATAL;
		begin.metadata.increment(&begin);
	}
	return OK;
}

iterator ft_bst_erase_one(container *this, iterator it)
{
	bst_node *n = it.bst.current;
	bst_node **nptr = n->parent->left == n ? &n->parent->left : &n->parent->right;
	iterator ret = it;
	ft_bst_iterator_increment(&ret);
	if (n->left && n->right)
	{
		bst_node *tmp = n->left;
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
	if (nptr == &this->bst.past_the_end.left)
		this->bst.past_the_end.right = this->bst.past_the_end.left;
	if (n == this->bst.last)
	{
		if (*nptr)
			this->bst.last = *nptr;
		else
			this->bst.last = n->parent;
	}
	if (n == this->bst.first)
	{
		if (*nptr)
			this->bst.first = *nptr;
		else
			this->bst.first = n->parent;
	}
	this->value_type_metadata.destructor(this->value_type_metadata, &n->data);
	free(n);
	this->size--;
	return ret;
}

int	ft_bst_iterator_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;
	return (((iterator *)l)->bst.current != ((iterator *)r)->bst.current);
}

data_type ft_bst_iterator_dereference(void *it)
{
	return (((iterator *)it)->bst
			.current->data);
}

data_type *ft_bst_iterator_reference(void *it)
{
	return (&((iterator *)it)->bst
			.current->data);
}

void *ft_bst_iterator_increment(void *it)
{
	if (((iterator *)it)->bst.current->right)
	{
		((iterator *)it)->bst.current = ((iterator *)it)->bst.current->right;
		while (((iterator *)it)->bst.current->left)
			((iterator *)it)->bst.current = ((iterator *)it)->bst.current->left;
	}
	else if (((iterator *)it)->bst.current->parent->left == ((iterator *)it)->bst.current)
		((iterator *)it)->bst.current = ((iterator *)it)->bst.current->parent;
	else
	{
		while (((iterator *)it)->bst.current->parent && ((iterator *)it)->bst.current->parent->left != ((iterator *)it)->bst.current)
			((iterator *)it)->bst.current = ((iterator *)it)->bst.current->parent;
		if (((iterator *)it)->bst.current->parent)
			((iterator *)it)->bst.current = ((iterator *)it)->bst.current->parent;
	}
	return it;
}

void *ft_bst_iterator_decrement(void *it)
{
	if (((iterator *)it)->bst.current->left)
	{
		((iterator *)it)->bst.current = ((iterator *)it)->bst.current->left;
		while (((iterator *)it)->bst.current->right)
			((iterator *)it)->bst.current = ((iterator *)it)->bst.current->right;
	}
	else if (((iterator *)it)->bst.current->parent->right == ((iterator *)it)->bst.current)
		((iterator *)it)->bst.current = ((iterator *)it)->bst.current->parent;
	else
	{
		while (((iterator *)it)->bst.current->parent && ((iterator *)it)->bst.current->parent->right != ((iterator *)it)->bst.current)
			((iterator *)it)->bst.current = ((iterator *)it)->bst.current->parent;
		if (((iterator *)it)->bst.current->parent)
			((iterator *)it)->bst.current = ((iterator *)it)->bst.current->parent;
	}
	return it;
}
