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
	int	i;
	int	sign;
	int	result;
	int	pow;
	int	len;

	pow = 1;
	sign = 1;
	len = 0;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = *str == 45 ? -1 : 1;
	str += (*str == 45 || *str == 43) ? 1 : 0;
	while (str[len] && str[len] > 47 && str[len] < 58)
		len++;
	i = 0;
	while (++i <= (int)len)
	{
		result += (int)(str[len - i] - 48) * (pow);
		pow *= 10;
	}
	return (result * sign);
}
