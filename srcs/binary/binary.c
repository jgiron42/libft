#include "binary.h"

mapped_file	map_file(char *filename)
{
	int fd;
#if (defined(WHITELIST) && defined(FT_USE_OPEN)) || (!defined(WHITELIST) && !defined(FT_USE_OPEN))
	fd = open(filename, O_RDONLY);
#else
	cursed_abort("can't map_file without fstat or syscall");
#endif
	if (fd == -1)
		return (mapped_file){NULL, 0, -1};
	struct stat st = {};
#if (defined(WHITELIST) && defined(FT_USE_STRERROR)) || (!defined(WHITELIST) && !defined(FT_USE_STRERROR))
	if (fstat(fd, &st) == -1)
		return (mapped_file){NULL, 0, -1};
#elif (defined(WHITELIST) && defined(FT_USE_SYSCALL)) || (!defined(WHITELIST) && !defined(FT_USE_SYSCALL))
	if (syscall(SYS_fstat, fd, &st) == -1)
		return (mapped_file){NULL, 0, -1};
#else
	cursed_abort("can't map_file without fstat or syscall");
#endif
#if (defined(WHITELIST) && defined(FT_USE_MMAP)) || (!defined(WHITELIST) && !defined(FT_USE_MMAP))
	return (mapped_file){mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0), st.st_size, fd};
#else
	cursed_abort("can't map_file without mmap");
#endif
}

void unmap_file(mapped_file f)
{
#if (defined(WHITELIST) && defined(FT_USE_MUNMAP)) || (!defined(WHITELIST) && !defined(FT_USE_MUNMAP))
	munmap(f.address, f.size);
#else
	cursed_abort("can't map_file without mmap");
#endif
#if (defined(WHITELIST) && defined(FT_USE_CLOSE)) || (!defined(WHITELIST) && !defined(FT_USE_CLOSE))
	close(f.fd);
#else
	cursed_abort("can't map_file without mmap");
#endif
}