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

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	if ((char)c == 0)
		return ((char *)s + ft_strlen(s));
	ret = NULL;
	while (*s != 0)
	{
		if (*s == (char)c)
			ret = (char *)s;
		s++;
	}
	return (ret);
}
