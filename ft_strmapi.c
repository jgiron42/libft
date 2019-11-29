/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:30:30 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/22 19:20:31 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*dst;

	if (!s || !f)
		return (NULL);
	i = -1;
	if (!(dst = ft_strdup(s)))
		return (NULL);
	while (dst[++i])
		dst[i] = (*f)(i, dst[i]);
	return (dst);
}
