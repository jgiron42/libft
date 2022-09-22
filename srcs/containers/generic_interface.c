#include "containers.h"


status ft_push_back(container *this, data_type data)
{
	if (this->metadata.interface_type == FT_SEQUENCE_CONTAINER && this->metadata.container.sequence.push_back != &ft_push_back)
	{
		if (this->metadata.container.sequence.push_back)
			return this->metadata.container.sequence.push_back(this, data);
		else if (this->metadata.container.sequence.insert_val && this->metadata.container.end)
			return this->metadata.container.sequence.insert_val(this, this->metadata.container.end(this), data);
	}
	else if (this->metadata.interface_type == FT_ASSOCIATIVE_CONTAINER)
	{
		if (this->metadata.container.associative.insert) {
			iterator ret = this->metadata.container.associative.insert(this, data);
			iterator end = this->metadata.container.end(this);
			return ret.metadata.compare(ret.metadata, &ret, &end) ? OK : KO;
		}
	}
	cursed_abort("Can't push_back on a sequence container that doesn't implement push_back or (insert_one and end) or an associative containers that implement insert");
}

status ft_push_front(container *this, data_type data)
{
	if (this->metadata.interface_type == FT_SEQUENCE_CONTAINER)
	{
		if (this->metadata.container.sequence.push_front && this->metadata.container.sequence.push_front != &ft_push_front)
			return this->metadata.container.sequence.push_front(this, data);
		else if (this->metadata.container.sequence.insert_val && this->metadata.container.begin)
			return this->metadata.container.sequence.insert_val(this, this->metadata.container.begin(this), data);
	}
	else if (this->metadata.interface_type == FT_ASSOCIATIVE_CONTAINER)
	{
		if (this->metadata.container.associative.insert) {
			iterator ret = this->metadata.container.associative.insert(this, data);
			iterator end = this->metadata.container.end(this);
			return ret.metadata.compare(ret.metadata, &ret, &end) ? OK : KO;
		}
	}
	cursed_abort("Can't push_front on a sequence container that doesn't implement push_front or (insert_one and begin) or an associative containers that implement insert");
}

void ft_pop_back(container *this)
{
	if (this->metadata.interface_type == FT_SEQUENCE_CONTAINER)
	{
		if (this->metadata.container.sequence.pop_back && this->metadata.container.sequence.pop_back != & ft_pop_back)
			this->metadata.container.sequence.pop_back(this);
	}
	else if (this->metadata.container.erase_one && this->metadata.container.end)
		this->metadata.container.erase_one(this, this->metadata.container.end(this));
	cursed_abort("Can't pop_back on a container that doesn't implement pop_back or (erase_one and end)");
}

void ft_pop_front(container *this)
{
	if (this->metadata.interface_type == FT_SEQUENCE_CONTAINER)
	{
		if (this->metadata.container.sequence.pop_front && this->metadata.container.sequence.pop_front != & ft_pop_front)
			this->metadata.container.sequence.pop_front(this);
	}
	else if (this->metadata.container.erase_one && this->metadata.container.begin)
		this->metadata.container.erase_one(this, this->metadata.container.begin(this));
	cursed_abort("Can't pop_front on a container that doesn't implement pop_front or (erase_one and begin)");
}

iterator	ft_erase_range(container *this, iterator begin, iterator end)
{
	if (this->metadata.container.erase_range && this->metadata.container.erase_range != &ft_erase_range)
		return this->metadata.container.erase_range(this, begin, end);
	else if (this->metadata.container.erase_one)
		while (begin.metadata.compare(begin.metadata, &begin, &end))
		{
			this->metadata.container.erase_one(this, begin);
			begin.metadata.increment(&begin);
		}
	cursed_abort("Can't erase_range on a container that doesn't implement erase_range or erase_one");
}

iterator	ft_find(container *this, data_type val)
{
	if (this->metadata.interface_type == FT_ASSOCIATIVE_CONTAINER &&
		this->metadata.container.associative.find &&
		this->metadata.container.associative.find != &ft_find)
		return this->metadata.container.associative.find(this, val);
	if (this->metadata.container.begin)
	{
		iterator it = this->metadata.container.begin(this);
		iterator end = this->metadata.container.end(this);
		data_type tmp =  it.metadata.dereference(&it);
		while (it.metadata.compare(it.metadata, &it, &end) && it.value_type_metadata.compare(it.value_type_metadata, &tmp, &val))
		{
			it.metadata.increment(&it);
			tmp =  it.metadata.dereference(&it);
		}
		return it;
	}
	cursed_abort("Can't find on a container that doesn't implement find or iterators");
}

iterator	ft_erase_val(container *this, data_type val)
{
	if (this->metadata.interface_type == FT_ASSOCIATIVE_CONTAINER &&
		this->metadata.container.associative.erase &&
		this->metadata.container.associative.erase != &ft_erase_val)
		return this->metadata.container.associative.erase(this, val);
	if (this->metadata.container.erase_one)
	{
		iterator it = ft_find(this, val);
		iterator end = this->end(this);
		if (!it.metadata.compare(it.metadata, &it, &end))
			return end;
		return this->metadata.container.erase_one(this, it);
	}
	cursed_abort("Can't erase_val on a container that doesn't implement erase_val or erase_one");
}
