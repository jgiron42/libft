#ifndef LIBFT_INTERNAL_PRINTF_H
# define LIBFT_INTERNAL_PRINTF_H
# include "../internal_ft_stdio.h"
# include <stdarg.h>
# include <stddef.h>

static const char *ft_printf_flag_char = "#0- +'";

enum ft_printf_internal_flags {
	FT_PRINTF_SHARP = 1,
	FT_PRINTF_ZERO = 2,
	FT_PRINTF_HYPHEN = 4,
	FT_PRINTF_SPACE = 8,
	FT_PRINTF_PLUS = 16,
	FT_PRINTF_SINGLE_QUOTE = 32,
};

static const char *ft_printf_length_modifier_char[] = {
"hh",
"h",
"l",
"ll",
"q",
"L",
"j",
"z",
"Z",
"t",
NULL,
};

static const int t_printf_length_modifier_size[] = {
		sizeof(char),
		sizeof(short),
		sizeof(long),
		sizeof(long long),
		-1, // flag for long double since bit mask wont work
		sizeof(intmax_t),
		sizeof(size_t),
		sizeof(size_t),
		sizeof(ptrdiff_t),
};

enum ft_printf_length_modifier {
	FT_PRINTF_LENGTH_hh = 0,
	FT_PRINTF_LENGTH_h,
	FT_PRINTF_LENGTH_l,
	FT_PRINTF_LENGTH_ll,
	FT_PRINTF_LENGTH_q,
	FT_PRINTF_LENGTH_L,
	FT_PRINTF_LENGTH_j,
	FT_PRINTF_LENGTH_z,
	FT_PRINTF_LENGTH_Z,
	FT_PRINTF_LENGTH_t,
	FT_PRINTF_LENGTH_DEFAULT,
};

typedef struct {
	enum ft_printf_internal_flags	flags;
	ssize_t							fwidth;
	ssize_t 						precision;
	enum ft_printf_length_modifier	length;
	int								argsize;
	char							conversion;
	const char						*restrict*format;
	va_list							arg;
	ft_FILE							*stream;
	size_t						begin;
}	internal_printf;

extern int saved_errno;

typedef int (*f)(internal_printf *);

int	handle_percent(internal_printf *conv, va_list arg);
int	handle_integer(internal_printf *conv, va_list arg);
int	handle_char(internal_printf *conv, va_list arg);
int	handle_string(internal_printf *conv, va_list arg);
int	handle_m(internal_printf *conv, va_list arg);
int	handle_n(internal_printf *conv, va_list arg);

int pad_right(internal_printf *conv, int size);
int pad_left(internal_printf *conv, int size);


//char *specifiers = "diouxXp" "eEfFgGaA" "csnm%"
//char *specifiers = "%";
//
//f conv_list[] = {
//
//};

int	parse_flag(internal_printf *, va_list arg);
int	parse_fwidth(internal_printf *, va_list arg);
int	parse_precision(internal_printf *, va_list arg);
int	parse_length(internal_printf *, va_list arg);
int	parse_conv(internal_printf *, va_list arg);

#endif //LIBFT_INTERNAL_PRINTF_H
