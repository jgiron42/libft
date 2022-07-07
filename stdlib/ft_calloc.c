/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 21:19:57 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:52:26 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (count > 0 && size > 0 && (SIZE_MAX / count < size))
		return (NULL);
	dst = malloc(count * size);
	if (!dst)
		return (NULL);
	while (i < (count * size) / sizeof(long int))
	{
		((long int *)dst)[i] = 0;
		i += sizeof(long int);
	}
	i = 0;
	while (i < (count * size))
	{
		dst[i] = 0;
		i++;
	}
	return ((void *)dst);
}
