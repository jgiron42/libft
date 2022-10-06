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

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	dest_l;
	unsigned int	src_l;

	if (dstsize == 0)
		return (ft_strlen(src));
	dest_l = (int)ft_strlen(dst);
	src_l = (int)ft_strlen(src);
	i = 0;
	if (dstsize < dest_l)
		src_l += dstsize;
	else
		src_l += dest_l;
	while (src[i] != '\0' && (dest_l + i) < dstsize - 1)
	{
		dst[i + dest_l] = src[i];
		i++;
	}
	if (dstsize >= dest_l)
		dst[i + dest_l] = '\0';
	return (src_l);
}
