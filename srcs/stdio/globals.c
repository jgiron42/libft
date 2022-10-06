#include "ft_stdio.h"

ft_FILE	stdio_files[3] = {
		{.fd = 0, .dontfree = true},
		{.fd = 1, .dontfree = true},
		{.fd = 2, .dontfree = true}
};

ft_FILE	*ft_last_file = NULL;