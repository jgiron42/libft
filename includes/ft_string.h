#ifndef LIBFT_FT_STRING_H
# define LIBFT_FT_STRING_H
# include "ft_def.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
size_t	ft_strcspn(const char *s, const char *reject);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strncat(char *dst, const char *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	*ft_strndup(const char *s1, size_t n);
char *ft_strpbrk(const char *s, const char *accept);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strspn(const char *s, const char *accept);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strtok(char *str, const char *delim);


#endif
