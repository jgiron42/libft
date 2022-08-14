#include "containers.h"

status atomic_constructor(type_metadata prop,  void *ptr)
{
	(void)prop;
	*(uint64_t *)ptr = 0;
	return OK;
}

void atomic_destructor(type_metadata prop,  void *ptr)
{
	(void)prop;
	*(uint64_t *)ptr = 0;
}

status atomic_copy(type_metadata prop,  void *dst, const void *src)
{
	(void)prop;
	*(uint64_t *)dst = *(uint64_t *)src;
	return OK;
}

status atomic_assign(type_metadata prop,  void *dst, const void *src)
{
	(void)prop;
	*(uint64_t *)dst = *(uint64_t *)src;
	return OK;
}

int	atomic_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;

	if (*(uint64_t *)l <
		*(uint64_t *)r)
		return -1;
	else if (*(uint64_t *)l > *(uint64_t *)r)
		return 1;
	return 0;
}

status byte_constructor(type_metadata prop,  void *ptr)
{
	(void)prop;
	*(char *)ptr = 0;
	return OK;
}

void byte_destructor(type_metadata prop,  void *ptr)
{
	(void)prop;
	*(char *)ptr = 0;
}

status byte_copy(type_metadata prop,  void *dst, const void *src)
{
	(void)prop;
	*(char *)dst = *(char *)src;
	return OK;
}

status byte_assign(type_metadata prop,  void *dst, const void *src)
{
	(void)prop;
	*(char *)dst = *(char *)src;
	return OK;
}

int	byte_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;

	if (*(char *)l <
	        *(char *)r)
		return -1;
	else if (*(char *)l > *(char *)r)
		return 1;
	return 0;
}

status pointer_constructor(type_metadata prop,  void *ptr)
{
	*(void **)ptr = malloc(prop.size);
	if (!*(void **)ptr)
		return (FATAL);
	bzero(*(void **)ptr, prop.size);
	return OK;
}

void pointer_destructor(type_metadata prop,  void *ptr)
{
	(void)prop;
	free(*(void **)ptr);
	*(void **)ptr = (data_type)0;
}

status pointer_copy(type_metadata prop,  void *dst, const void *src)
{
	if (*(void **)dst)
		free(*(void **)dst);
	*(void **)dst = malloc(prop.size);
	if (!*(void **)dst)
		return (FATAL);
	memcpy(*(void **)dst, *(void **)src, prop.size);
	return OK;
}

status pointer_assign(type_metadata prop,  void *dst, const void *src)
{
	memcpy(*(void **)dst, *(void **)src, prop.size);
	return OK;
}

int	pointer_compare(type_metadata prop, void *l, void *r)
{
	return (ft_memcmp(*(void**)l, *(void **)r, prop.size));
}
