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
			}
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

status path_pop(container *this)
{
	if (!this->vector.data)
		return FATAL;
	if (!ft_string_size(this))
		return KO;
	char *tmp = ft_strrchr(this->vector.data, '/');
	if (tmp)
	{
		*tmp = '\0';
		this->size = tmp - this->vector.data + 1;
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