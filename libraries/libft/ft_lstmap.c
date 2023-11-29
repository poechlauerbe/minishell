/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:16:00 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/13 09:33:15 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*lst_elem;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	map = NULL;
	while (lst)
	{
		temp = f(lst->content);
		lst_elem = ft_lstnew(temp);
		if (!lst_elem)
		{
			(del)(temp);
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, lst_elem);
		lst = lst->next;
	}
	return (map);
}
