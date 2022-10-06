/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 06:07:37 by jgiron            #+#    #+#             */
/*   Updated: 2022/04/19 06:07:56 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	**tmp;

	ret = NULL;
	tmp = &ret;
	while (lst)
	{
		*tmp = ft_lstnew(f(lst->content));
		if (!*tmp)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		tmp = &(*tmp)->next;
		lst = lst->next;
	}
	return (ret);
}
