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

#include "ft_string.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((dst <= src + len) && (dst > src))
	{
		while (len-- > 0) {
			*(char *) (dst + len) =
					*(char *) (src + len);
		}
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
