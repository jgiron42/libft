/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 21:19:57 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/06 12:08:14 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*dst;

	i = -1;
	if (!(dst = malloc(count * size)))
		return (NULL);
	while (++i < count * size)
		dst[i] = 0;
	return ((void *)dst);
}
