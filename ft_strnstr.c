/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 20:39:03 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/29 14:29:48 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	i = -1;
	if (!haystack)
		return (NULL);
	if (haystack[0] == 0 && needle[0] != 0)
		return (NULL);
	if (haystack[0] == 0 && needle[0] == 0)
		return ((char *)haystack);
	while (haystack[++i] && (i < (int)len || len == 0))
	{
		j = 0;
		while (needle[j] == haystack[i + j] &&
		needle[j] && haystack[i + j] && i + j < (int)len)
			j++;
		if (needle[j] == 0)
			return ((char *)haystack + i);
	}
	return (NULL);
}
