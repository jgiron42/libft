/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:27:39 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:23:36 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*str;

	str = dst;
	if (((dst - src) <= (int)len) && ((dst - src) > 0))
	{
		i = len;
		while (--i + 1 > 0)
			*(str + i) = *(char *)(src + i);
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
