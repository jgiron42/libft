/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 19:24:03 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:49:10 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*get_next_word(char *s, char c)
{
	unsigned char	prev;

	prev = c;
	while (*s)
	{
		if (*s != c && prev == c)
			return (s);
		prev = *s;
		s++;
	}
	return (s);
}

static size_t	count_word(char *s, unsigned char c)
{
	size_t			ret;
	unsigned char	prev;

	ret = 0;
	prev = c;
	while (*s)
	{
		if (*s != c && prev == c)
			ret++;
		prev = *s;
		s++;
	}
	return (ret);
}

void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char		*end;
	char		**ret;
	int			i;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_word((char *)s, c) + 1));
	i = 0;
	if (!ret)
		return (NULL);
	while (*s)
	{
		s = (const char *)get_next_word((char *)s, c);
		if (!*s)
			break ;
		end = ft_strchr(s, c);
		if (!end)
			end = (char *)s + ft_strlen(s);
		ret[i] = ft_strndup(s, end - s);
		if (!ret[i])
			return (ft_free_split(ret), NULL);
		s = end;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
