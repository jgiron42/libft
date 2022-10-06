/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:27:48 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/27 13:40:22 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(int n)
{
	int	len;

	len = 1 + (n < 0);
	while (!(n > -10 && n < 10))
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned char	*result;
	size_t			len;
	long long int	nbr;

	nbr = (long long int)n;
	if (!n)
		return (ft_strdup("0"));
	len = ft_nbrlen(n);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	result[len] = 0;
	while (nbr)
	{
		--len;
		result[len] = '0' + nbr % 10;
		nbr /= 10;
	}
	return ((char *)result);
}
