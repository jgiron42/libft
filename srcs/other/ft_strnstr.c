/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 20:39:03 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:44:11 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack && haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[i + j] && i + j < len)
			j++;
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
