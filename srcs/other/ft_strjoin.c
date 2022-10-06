/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:53:23 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/22 19:17:37 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	dst = malloc(i + j + 1);
	if (!dst)
		return (NULL);
	dst[i + j] = 0;
	while (--j + 1 > 0)
		dst[i + j] = s2[j];
	j++;
	while (--i + 1 > 0)
		dst[i + j] = s1[i];
	return (dst);
}
