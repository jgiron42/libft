/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:08:14 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/22 19:16:24 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		return ((char *)ft_memset(malloc(1), 0, 1));
	if (!(dst = malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = 0;
	return (dst);
}
