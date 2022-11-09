#include "containers.h"
#include "ft_string.h"

status ft_string(void *dst, char *str)
{
	*(container *)dst = (container){
			.type = FT_VECTOR,
			.init = true,
			.value_type_metadata = BYTE_TYPE,
			.size = ft_strlen(str) + 1,
			.vector = {
					.data = ft_strdup(str),
					.capacity = ft_strlen(str) + 1,
					.align = sizeof(char),
			},
			.begin = &ft_vector_begin,
			.end = &ft_vector_end,
			.clear = &ft_vector_clear,
			.destroy = &ft_vector_destructor,
			.copy = &ft_vector_copy,
	};
	if ((*(container *)dst).vector.data == NULL)
		return FATAL;
	return OK;
}

status	ft_string_assign(type_metadata meta, void *dst, void *src)
{
	(void)meta;
	*((container *)dst) = *((container *)src);
	((container *)src)->size = 0;
	((container *)src)->vector.capacity = 0;
	((container *)src)->vector.data = 0;
	return OK;
}

status	ft_string_copy(type_metadata meta, void *dst, void *src)
{
	(void)meta;
	*((container *)dst) = *((container *)src);
	((container *)dst)->vector.data = malloc(((container *)dst)->vector.capacity);
	if (!((container *)dst)->vector.data)
		return FATAL;
	ft_strcpy(((container *)dst)->vector.data, ((container *)src)->vector.data);
	return OK;
}

int	ft_string_compare(type_metadata meta, void* left, void* right)
{
	(void)meta;
	if (!((container *)right)->vector.data && !((container *)left)->vector.data)
		return 0;
	else if (!((container *)left)->vector.data)
		return -1;
	else if (!((container *)right)->vector.data)
		return 1;
	else
		return ft_strcmp(((container *)left)->vector.data, ((container *)right)->vector.data);
}

void	ft_string_clear(container *this)
{
	if (this->size)
	{
		this->size = 1;
		this->vector.data[0] = 0;
	}
}

char	*ft_string_c_str(container *this)
{
	return (char *)this->vector.data;
}

size_t ft_string_size(const container *src)
{
	return src->size - 1;
}

status ft_string_push_back(container *this, data_type data)
{
	if (ft_vector_push_back(this, 0) != OK)
		return FATAL;
	this->vector.data[this->size - 2] = (char)(intmax_t)data;
	return OK;
}

void ft_string_pop_back(container *this)
{
	ft_vector_pop_back(this);
	this->vector.data[this->size - 1] = 0;
}

status	ft_string_append(container *this, char *str)
{
	size_t len = ft_strlen(str);
	if (this->size + len > this->vector.capacity && ft_vector_expand(this, len) != OK)
		return FATAL;
	ft_strcpy(this->vector.data + this->size - 1, str);
	this->size += len;
	return OK;
}

status path_pop(container *this)
{
	if (!this->vector.data)
		return FATAL;
	if (!ft_string_size(this))
		return KO;
	char *tmp = ft_strrchr(this->vector.data, '/');
	if (tmp)
	{
		if (tmp == this->vector.data)
		{
			tmp[1] = 0;
			this->size = 2;
		}
		else
		{
			*tmp = '\0';
			this->size = tmp - this->vector.data + 1;
		}
	}
	else
	{
		this->size = 1;
		this->vector.data[0] = '\0';
	}
	return OK;
}

status path_push(container *this, char *component)
{
	register bool	slash = this->size > 1 && this->vector.data[this->size - 2] != '/';
	size_t len = ft_strlen(component);
	if (this->size + len + slash > this->vector.capacity && ft_vector_expand(this, len + slash) != OK)
			return FATAL;
	if (slash)
	{
		this->vector.data[this->size - 1] = '/';
		this->vector.data[this->size] = 0;
		this->size++;
	}
	ft_strcpy(this->vector.data + this->size - 1, component);
	this->size += len;
	return OK;
}