/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcasecmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:37:10 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/28 17:03:18 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	if (!s1)
		return (0);
	while ((*s1 != '\0' || *s2 != '\0'))
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return ((int)(ft_tolower(*s1) - ft_tolower(*s2)));
		s1++;
		s2++;
	}
	return (0);
}
