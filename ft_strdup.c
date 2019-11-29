/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:06:23 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/13 21:37:43 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;

	if (!(dest = malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	dest = ft_memcpy(dest, s1, ft_strlen(s1) + 1);
	return (dest);
}
