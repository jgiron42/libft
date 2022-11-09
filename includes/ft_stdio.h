#ifndef LIBFT_FT_STDIO_H
# define LIBFT_FT_STDIO_H
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
#include "ft_def.h"
# define ft_EOF EOF
# define BUF_REALLOC 10
# define ft_stdin ((ft_FILE *)&stdio_files[0])
# define ft_stdout ((ft_FILE *)&stdio_files[1])
# define ft_stderr ((ft_FILE *)&stdio_files[2])

# define ft_input_string_stream(s) (ft_FILE){.rbuf = s,.rbuflen = ft_strlen(s),.rbufcap = ft_strlen(s),.flags = FT_STDIO_ISTRINGSTREAM,}

enum	ft_stdio_flags {
	FT_STDIO_R = 1,
	FT_STDIO_RW,
	FT_STDIO_W,
	FT_STDIO_WR,
	FT_STDIO_A,
	FT_STDIO_AR,
	FT_STDIO_STRINGSTREAM,
	FT_STDIO_ISTRINGSTREAM
};

typedef struct
{
	ssize_t pos;
}		ft_fpos_t;

typedef struct	s_FILE
{
	int					fd;
	enum ft_stdio_flags flags;
	bool				eof;
	bool				error;
	bool				dontfree;
	ft_fpos_t			position;
	char				*rbuf;
	size_t				rbuflen;
	size_t				rbufcap;
	char				*wbuf;
	size_t				wbuflen;
	size_t				wbufcap;
	char				buf_flag;
	bool				free_wbuf;
	struct s_FILE		*prev;
	struct s_FILE		*next;
}				ft_FILE;

extern ft_FILE	*ft_last_file;
extern ft_FILE			stdio_files[3];

ft_FILE	*ft_fopen(const char *filename, const char *mode);
ft_FILE	*ft_freopen(const char *path, const char *mode, ft_FILE *stream);
//TODO: ft_fdopen

int		ft_fclose(ft_FILE *stream);
size_t	ft_fread(void *ptr, size_t size, size_t nmemb, ft_FILE *stream);
size_t	ft_fwrite(const void *ptr, size_t size, size_t nmemb, ft_FILE *stream);
int		ft_feof(ft_FILE *stream);
int		ft_ferror(ft_FILE *stream);
int		ft_fileno(ft_FILE *stream);
void	ft_clearerr(ft_FILE *stream);
int		ft_fflush(ft_FILE *stream);
int		ft_fseek(ft_FILE *, long, int);
long	ft_ftell(ft_FILE *);
int		ft_fsetpos(ft_FILE *, const ft_fpos_t *);
int		ft_fgetpos(ft_FILE *, ft_fpos_t *);
void	ft_rewind(ft_FILE *stream);

int		ft_fgetc(ft_FILE *stream);
char	*ft_fgets(char *restrict s, int n, ft_FILE *restrict stream);
char    *ft_gets(char *);
int		ft_getc(ft_FILE *stream);
int		ft_getchar(void);
//TODO: ft_ungetc

int		ft_fputc(int, ft_FILE *);
int		ft_fputs(const char *restrict s, ft_FILE *restrict stream);
int		ft_putc(int c, ft_FILE *stream);
int		ft_putchar(int c);
int		ft_puts(const char *s);

void	ft_perror(const char *prefix);

int		ft_remove(const char *pathname);
int		ft_rename(const char *oldpath, const char *newpath);

int		ft_ungetc(int c, ft_FILE *stream);
int		ft_ungets(const char *s, ft_FILE *stream);
ssize_t  ft_getdelim(char **restrict lineptr, size_t *restrict n, int delim, ft_FILE *restrict stream);
ssize_t  ft_getline(char **restrict lineptr, size_t *restrict n, ft_FILE *restrict stream);

int		ft_setvbuf(ft_FILE *restrict stream, char *restrict buf, int type, size_t size);
void	ft_setbuf(ft_FILE *restrict stream, char *restrict buf);


int      ft_vfprintf(ft_FILE *restrict, const char *restrict, va_list);
int		ft_fprintf(ft_FILE *stream, const char *format, ...) __attribute__((format(printf, 2, 3)));
int		ft_vprintf(const char *format, va_list);
int		ft_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));
int		ft_vsprintf(char *s, const char *format, va_list arg);
int		ft_sprintf(char *s, const char *format, ...) __attribute__((format(printf, 2, 3)));
int		ft_vsnprintf(char *s, size_t size, const char *format, va_list arg);
int		ft_snprintf(char *s, size_t size, const char *format, ...) __attribute__((format(printf, 3, 4)));

#endif
