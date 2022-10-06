#include "internal_ft_stdio.h"

ssize_t  ft_getdelim(char **restrict lineptr, size_t *restrict n, int delim, ft_FILE *restrict stream) // TODO: handle einval
{
	ssize_t ret;
	size_t to_read = FT_STDIO_GETDELIM_BUFFER_SIZE;
	ssize_t read = 0;
	char *tmp;

	if (*lineptr)
		to_read = *n;
	else
	{
		*lineptr = malloc(FT_STDIO_GETDELIM_BUFFER_SIZE);
		if (!*lineptr)
			return -1;
		*n = to_read;
	}
//	printf("<>");
	while (1) {
		ret = ft_get_delim_buffered(*lineptr + read, to_read, stream, delim);
//		printf("=> [%s|%s|%zd|%zu]", *lineptr + read, *lineptr + read - 3, ret, read);
		if (ret == -1 || (!ret && !read))
			return -1;
		read += ret;
		if (!ret || ft_feof(stream) || (read > 0 && *(*lineptr + read - 1) == delim))
			break;
		tmp = malloc(read + FT_STDIO_GETDELIM_BUFFER_SIZE);
		if (!tmp)
			return -1;
		*n = read + FT_STDIO_GETDELIM_BUFFER_SIZE;
		to_read = FT_STDIO_GETDELIM_BUFFER_SIZE;
		memcpy(tmp, *lineptr, read + 1);
		free(*lineptr);
		*lineptr = tmp;
	};
//	printf("{%s}", *lineptr);
	return read;
}