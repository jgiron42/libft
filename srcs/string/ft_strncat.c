/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:35:15 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/28 16:20:46 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	ft_strncpy(dst + ft_strlen(dst), src, n);
	if (ft_strlen(src) > n)
		dst[ft_strlen(dst) + n + 1] = 0;
	return (dst);
}
