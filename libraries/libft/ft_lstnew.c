/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:17:02 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/09 13:20:52 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nn;

	nn = (t_list *)malloc(sizeof(t_list));
	if (nn == NULL)
		return (NULL);
	nn->content = content;
	nn->next = NULL;
	return (nn);
}
