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

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	sign;
	long int	result;
	int			pow;
	int			len;

	pow = 1;
	len = 0;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = (*str == '-');
	str += (*str == '-' || *str == '+');
	while (str[len] && str[len] >= '0' && str[len] <= '9')
		len++;
	i = 0;
	while (++i <= (int)len && result <= (INT_MAX + sign))
	{
		result += (int)(str[len - i] - 48) *pow;
		pow *= 10;
	}
	if (i <= len)
		return (-1);
	return ((int)(result * (1 - 2 * sign)));
}
