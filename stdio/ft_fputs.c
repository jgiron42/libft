#include "ft_stdio.h"

int      ft_fputs(const char *restrict s, ft_FILE *restrict stream) {
	register size_t len = ft_strlen(s);
	if (ft_fwrite(s, 1, len, stream) != len)
		return (1);
	return (ft_EOF);
}