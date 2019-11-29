/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:27:39 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/11 21:19:36 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int		i;
	char	*str;

	str = dst;
	i = -1;
	while (++i < (int)n)
	{
		*(str + i) = *(char *)(src + i);
		if (*(char *)(src + i) == (char)c)
			return (dst + i + 1);
	}
	return (NULL);
}
