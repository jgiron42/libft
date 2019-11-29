/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:52:51 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/12 14:47:17 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = -1;
	ptr = NULL;
	while (s[++i] != 0)
		if (s[i] == (char)c)
			ptr = (char *)s + i;
	if ((char)c == 0)
		return ((char *)s + i);
	return (ptr);
}
