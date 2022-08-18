#include "containers.h"

status ft_string(void *dst, char *str)
{
	*(container *)dst = (container){
			.type = FT_VECTOR,
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

char	*ft_string_c_str(container *this)
{
	return (char *)this->vector.data;
}

size_t ft_string_size(const container *src)
{
	return src->size - 1;
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