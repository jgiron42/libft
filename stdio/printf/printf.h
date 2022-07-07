//
// Created by joachim on 6/26/22.
//

#ifndef LIBFT_PRINTF_H
#define LIBFT_PRINTF_H
#include "../ft_stdio.h"
int      ft_vfprintf(ft_FILE *restrict, const char *restrict, va_list);
int		ft_fprintf(ft_FILE *stream, const char *format, ...);
int		ft_vprintf(const char *format, va_list);
int		ft_printf(const char *format, ...);

#endif //LIBFT_PRINTF_H
