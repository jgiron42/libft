#ifndef LIBFT_INTERNAL_FT_STDIO_H
#define LIBFT_INTERNAL_FT_STDIO_H
#include "ft_stdio.h"
#include "../libft.h"
#ifndef FT_STDIO_GETDELIM_BUFFER_SIZE
# define FT_STDIO_GETDELIM_BUFFER_SIZE 10
#endif
int	ft_expand_buf(ft_FILE *stream, int n);
ssize_t ft_get_delim_buffered(char *restrict s, size_t n, ft_FILE *restrict stream, int delim);
size_t	wrapped_read(void *ptr, size_t size, size_t nmemb, ft_FILE *stream);
#endif //LIBFT_INTERNAL_FT_STDIO_H
