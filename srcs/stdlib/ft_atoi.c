/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:32:04 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/28 14:07:33 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * POSIX and glibc compliant atoi (see: man 3 atoi)
 */
int	ft_atoi(const char *nptr)
{
	int errno_save = errno;
	errno = 0;
	long int ret = ft_strtol(nptr, NULL, 10);
	if (ret < INT_MIN || ret > INT_MAX || errno)
		ret = 0;
	errno = errno_save;
	return ((int)ret);
}
