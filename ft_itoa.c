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

	len = n < 0 ? 2 : 1;
	while (!(n > -10 && n < 10))
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char			*result;
	size_t			i;
	size_t			len;
	long long int	nbr;

	nbr = (long long int)n;
	len = ft_nbrlen(n);
	i = 1;
	if (!(result = malloc(len + 1)))
		return (NULL);
	result[len] = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = 45;
	}
	if (nbr <= -10 || nbr >= 10)
		result[len - i++] = 48 + nbr % 10;
	else
		nbr *= 10;
	while ((nbr /= 10) >= 10)
		result[len - i++] = 48 + nbr % 10;
	result[len - i++] = 48 + nbr % 10;
	return (result);
}
