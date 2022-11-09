#ifndef LIBFT_FT_STDLIB_H
# define LIBFT_FT_STDLIB_H
# include "ft_def.h"

int ft_abs(int j);
long ft_labs(long j);
long long ft_llabs(long long j);
char	*ft_getenv(const char *name);
double	ft_atof(const char *nptr);
double	ft_strtod(const char *nptr, char **endptr);
float	ft_strtof(const char *nptr, char **endptr);
long double	ft_strtold(const char *nptr, char **endptr);
long	ft_strtol(const char *nptr, char **endptr, int base);
long long	ft_strtoll(const char *nptr, char **endptr, int base);
long	ft_atol(const char *nptr);
long long	ft_atoll(const char *nptr);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif //LIBFT_FT_STDLIB_H
