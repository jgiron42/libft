#ifndef LIBFT_BINARY
# define LIBFT_BINARY

# include "libft.h"
# include <elf.h>
# include <sys/mman.h>
#if (defined(WHITELIST) && defined(FT_USE_STRERROR)) || (!defined(WHITELIST) && !defined(FT_USE_STRERROR))
#include <sys/stat.h>
#elif (defined(WHITELIST) && defined(FT_USE_SYSCALL)) || (!defined(WHITELIST) && !defined(FT_USE_SYSCALL))
#include <syscall.h>
#endif


# define is_valid_pointer(file, ptr, t) (((void*)ptr) >= (void*)(file).address && (void*)(ptr) + sizeof(t) <= (void*)(file).address + (file).size)
# define is_valid_string(file, ptr) (is_valid_pointer((file), (ptr), char) && ft_memchr((void*)(ptr), 0, ((file).address + (file).size) - ((void*)ptr)))

typedef struct {
	void	*address;
	size_t	size;
	int		fd;
}		mapped_file;

mapped_file	map_file(char *filename);
void		unmap_file(mapped_file f);

#endif
