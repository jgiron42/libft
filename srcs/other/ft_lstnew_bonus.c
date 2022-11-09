/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 06:08:04 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:08:15 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	*ret = (t_list){content, NULL};
	return (ret);
}
