/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:52:51 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/12 14:42:59 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while ((s[i] != 0) && (s[i] != (char)c))
		i++;
	if (s[i] == 0 && (char)c != 0)
		return (NULL);
	ptr = (char *)s;
	c = 0;
	return (ptr + i);
}
