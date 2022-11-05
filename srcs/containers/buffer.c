#include "containers.h"

status ft_buffer(void *dst, char *buf, size_t size, size_t cap)
{
	*(container *)dst = (container){
			.type = FT_VECTOR,
			.init = true,
			.value_type_metadata = BYTE_TYPE,
			.size = size,
			.vector = {
					.data = cap != 0 ? malloc(cap) : NULL,
					.capacity = cap,
					.align = sizeof(char),
			},
			.begin = &ft_vector_begin,
			.end = &ft_vector_end,
			.clear = &ft_vector_clear,
			.destroy = &ft_vector_destructor,
			.copy = &ft_vector_copy,
	};
	if (cap && (*(container *)dst).vector.data == NULL)
		return FATAL;
	ft_memcpy((*(container*)dst).vector.data, buf, size);
	return OK;
}

status ft_buffer_assign(container *this, char *buf, size_t size)
{
	if (size > this->vector.capacity && ft_vector_expand(this, size - this->vector.capacity) != OK)
		return FATAL;
	ft_memcpy(this->vector.data, buf, size);
	this->size = size;
	return OK;
}