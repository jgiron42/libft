/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:27:39 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/27 13:29:46 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*str;

	if (!dst && !src)
		return (NULL);
	str = dst;
	i = -1;
	if (((dst - src) <= (int)len) && ((dst - src) > 0))
	{
		i = len;
		while (--i + 1 > 0)
			*(str + i) = *(char *)(src + i);
		return (dst);
	}
	else
	{
		while (++i < len)
			*(str + i) = *(char *)(src + i);
		return (dst);
	}
}
