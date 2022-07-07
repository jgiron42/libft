/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:32:04 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/28 14:07:33 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * POSIX and glibc compliant atoll (see: man 3 atoll)
 */
long long	ft_atoll(const char *nptr)
{
	int errno_save = errno;
	errno = 0;
	long long ret = ft_strtoll(nptr, NULL, 10);
	if (errno)
		ret = 0;
	errno = errno_save;
	return (ret);
}
