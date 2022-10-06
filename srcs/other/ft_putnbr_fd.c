/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:29:07 by jgiron            #+#    #+#             */
/*   Updated: 2019/11/12 17:23:02 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		nb[12];
	long int	ln;
	int			i;

	if (!n)
		return (ft_putstr_fd("0", fd));
	ln = n;
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln = -ln;
	}
	nb[11] = 0;
	i = 10;
	while (ln)
	{
		nb[i] = ln % 10 + '0';
		ln /= 10;
		i--;
	}
	i++;
	write(fd, nb + i, 12 - i - 1);
}
