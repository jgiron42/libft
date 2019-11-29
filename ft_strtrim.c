/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:56:57 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/22 19:18:40 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strtrim_set_start(char *s1, char *set)
{
	size_t	i;
	size_t	start;

	i = -1;
	start = 0;
	while (set[++i] && s1[start])
		if (s1[start] == set[i])
		{
			start++;
			i = -1;
		}
	return (start);
}

static size_t	ft_strtrim_set_end(char *s1, char *set)
{
	int		end;
	size_t	i;

	end = 0;
	while (s1[end])
		end++;
	end--;
	i = -1;
	while (set[++i] && end >= 0)
		if (s1[end] == set[i])
		{
			end--;
			i = -1;
		}
	return (end + 1);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = ft_strtrim_set_start((char *)s1, (char *)set);
	end = ft_strtrim_set_end((char *)s1, (char *)set);
	if (end <= start)
		return ((char *)ft_memset(malloc(1), 0, 1));
	return (ft_substr((char *)s1, start, end - start));
}
