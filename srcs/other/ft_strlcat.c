/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:35:15 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/28 16:20:46 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strnlen(const char *str, size_t max)
{
	size_t	a;

	a = 0;
	while (a < max && str[a])
		a++;
	return (a);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_l;
	size_t	src_l;

	if (dstsize == 0)
		return (ft_strlen(src));
	dest_l = ft_strnlen(dst, dstsize);
	src_l = ft_strlen(src);
	i = 0;
	while (src[i] && (dest_l + i) < dstsize - 1)
	{
		dst[i + dest_l] = src[i];
		i++;
	}
	if (dest_l + i < dstsize)
		dst[dest_l + i] = 0;
	return (src_l + dest_l);
}
