/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:40:41 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:12:28 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <unistd.h>
# include <strings.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include <errno.h>
# include <error.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>
# include <signal.h>
# include "srcs/stdio/printf/printf.h"

typedef enum {
	OK,
	KO,
	FATAL,
}		status;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

extern char *ft_optarg;
extern int ft_optind, ft_opterr, ft_optopt;
extern char **environ;

void	cursed_abort(char *str) __attribute__((noreturn));
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strcspn(const char *s, const char *reject);
size_t	ft_strspn(const char *s, const char *accept);
char *ft_strpbrk(const char *s, const char *accept);
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
time_t	ft_time(time_t *tloc);
bool	ft_posixly_correct();
int		ft_getopt(int argc, char * const argv[], const char *optstring);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memswap(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcasecmp(const char *s1, const char *s2);
int		ft_strncasecmp(const char *s1, const char *s2, size_t n);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strncat(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_append(char **str, char *to_append);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_free_split(char **array);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

bool int_validator(char *str, bool is_signed, char terminator);
void	*ft_lazy_realloc(void *ptr, size_t size);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
# include "srcs/containers/containers.h"
# include "srcs/macro.h"
#endif
