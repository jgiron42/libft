#include "containers.h"

status ft_bheap(type_metadata meta, void *dst)
{
	*(container *)dst = (container){
		.type = FT_BHEAP,
		.value_type_metadata = meta,
		.size = 0,
		.bheap = {
				.root = NULL,
		}
	};
	return OK;
}

data_type ft_bheap_min(container *this)
{
	return this->bheap.root->data;
}

status	ft_bheap_insert(container *this, data_type data)
{
	btree_node *new_node = malloc(sizeof(btree_node));
	if (!new_node)
		return FATAL;
	this->value_type_metadata.copy(this->value_type_metadata, &new_node->data, &data);
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	if (!this->bheap.root)
	{
		this->bheap.root = new_node;
		this->size++;
		return OK;
	}
	btree_node *current = this->bheap.last;

}