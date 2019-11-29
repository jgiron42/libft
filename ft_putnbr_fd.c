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

static void	ft_putnbr_display(int t, int n[], int m, int fd)
{
	while (t > 0 && m == 0)
	{
		write(fd, &n[t], 1);
		t--;
	}
	if (m == 1)
	{
		write(fd, &"-2147483648", 11);
	}
}

static void	ft_putnbr_process(int n[], int nb, int m, int fd)
{
	int	t;

	t = 1;
	while (nb >= 10 && m == 0)
	{
		n[t] = (nb % 10) + 48;
		t++;
		nb = nb / 10;
	}
	n[t] = nb + 48;
	ft_putnbr_display(t, n, m, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	int s;
	int nb[11];
	int m;

	m = 0;
	s = 1;
	if (n == -2147483648)
		m = 1;
	if (n < 0 && m == 0)
	{
		write(fd, &"-", 1);
		n = -n;
	}
	ft_putnbr_process(nb, n, m, fd);
}
