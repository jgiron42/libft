/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncasecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:37:10 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:43:25 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 != '\0' || *s2 != '\0') && n > 0)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return ((int)(ft_tolower(*s1) - ft_tolower(*s2)));
		s1++;
		s2++;
		n--;
	}
	return (0);
}
