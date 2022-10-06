/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:06:23 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/13 21:37:43 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(s1);
	if (len > n)
		len = n;
	dest = malloc(len + 1);
	if (dest)
		ft_strlcpy(dest, s1, len + 1);
	return (dest);
}
