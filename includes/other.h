#ifndef LIBFT_OTHER_H
#define LIBFT_OTHER_H
#include "ft_def.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;


void	cursed_abort(char *str) __attribute__((noreturn));
time_t	ft_time(time_t *tloc);
bool	ft_posixly_correct();
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

void	*ft_memswap(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_append(char **str, char *to_append);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_free_split(char **array);
#endif
