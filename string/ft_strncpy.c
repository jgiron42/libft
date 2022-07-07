/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 11:59:57 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/29 17:48:34 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*tmp;

	tmp = dst;
	while (*src && n > 0)
	{
		*tmp = *src;
		src++;
		tmp++;
		n--;
	}
	while (n > 0)
	{
		*tmp = 0;
		tmp++;
		n--;
	}
	return (dst);
}
