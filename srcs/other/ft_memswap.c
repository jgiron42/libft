/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:27:39 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:22:28 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memswap(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n / sizeof(long int))
	{
		long int tmp = ((long int *)dst)[i];
		((long int *)dst)[i] = ((long int *)src)[i];
		((long int *)src)[i] = tmp;
		i++;
	}
	i *= sizeof(long int);
	while (i < n)
	{
		char tmp = ((char *)dst)[i];
		((char *)dst)[i] = ((char *)src)[i];
		((char *)src)[i] = tmp;
		i++;
	}
	return (dst);
}
