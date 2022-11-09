/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 11:59:57 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:43:47 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	length;

	length = 0;
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0' && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	i = 0;
	while (src[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}
