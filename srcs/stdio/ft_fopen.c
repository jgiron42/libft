#include "internal_ft_stdio.h"

static int get_oflag(const char *mode)
{
	const struct {char s[3]; int f;} map[] = {
			{"r", O_RDONLY},
			{"r+", O_RDWR},
			{"w", O_WRONLY | O_CREAT | O_TRUNC},
			{"w+", O_RDWR | O_CREAT | O_TRUNC},
			{"a", O_APPEND | O_CREAT},
			{"a+", O_RDWR | O_CREAT},
	};
	if (!mode)
		return (0);
	for (size_t i = 0; i < sizeof map / sizeof map[0]; i++)
	{
		if (!ft_strcmp(map[i].s, mode))
			return (map[i].f);
	}
	return (0);
}

static enum ft_stdio_flags get_flag(const char *mode)
{
	const struct {char s[3]; enum ft_stdio_flags f;} map[] = {
			{"r", FT_STDIO_R},
			{"r+", FT_STDIO_RW},
			{"w", FT_STDIO_W},
			{"w+", FT_STDIO_WR},
			{"a", FT_STDIO_A},
			{"a+", FT_STDIO_AR},
	};
	if (!mode)
		return (0);
	for (size_t i = 0; i < sizeof map / sizeof map[0]; i++)
	{
		if (!ft_strcmp(map[i].s, mode))
			return (map[i].f);
	}
	return (0);
}

int	ft_internal_fopen(const char *filename, const char *mode, ft_FILE *stream)
{
	*stream = (ft_FILE){};
	stream->flags = get_flag(mode);
	if (!stream->flags)
	{
		errno = EINVAL;
		return (1);
	}
	stream->fd = open(filename, get_oflag(mode), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (stream->fd == -1)
		return (1);
	return (0);
}

ft_FILE *ft_fopen(const char *filename, const char *mode)
{
	ft_FILE ret = {};
	if (ft_internal_fopen(filename, mode, &ret))
		return (NULL);
	ft_FILE	*retptr = malloc(sizeof ret);
	if (!retptr)
		return (NULL);
	ft_memcpy(retptr, &ret, sizeof ret);
	if (ft_last_file)
	{
		ft_last_file->next = retptr;
		retptr->prev = ft_last_file;
	}
	else
		ft_last_file = retptr;
	return retptr;
}

ft_FILE	*ft_freopen(const char *path, const char *mode, ft_FILE *stream)
{
	ft_fflush(stream);
	if (close(stream->fd) == -1)
		return (NULL);
	free(stream->rbuf);
	free(stream->wbuf);
	if (ft_internal_fopen(path, mode, stream))
		return NULL;
	return (stream);
}
