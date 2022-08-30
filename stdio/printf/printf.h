#ifndef LIBFT_PRINTF_H
#define LIBFT_PRINTF_H
#include <stdarg.h>
#include "../ft_stdio.h"

int      ft_vfprintf(ft_FILE *restrict, const char *restrict, va_list);
int		ft_fprintf(ft_FILE *stream, const char *format, ...) __attribute__((format(printf, 2, 3)));
int		ft_vprintf(const char *format, va_list);
int		ft_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));
int		ft_vsprintf(char *s, const char *format, va_list arg);
int		ft_sprintf(char *s, const char *format, ...) __attribute__((format(printf, 2, 3)));

#endif //LIBFT_PRINTF_H
