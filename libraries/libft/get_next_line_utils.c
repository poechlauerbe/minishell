/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:33:18 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 17:33:46 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_strlen(t_list1 *lst)
{
	int	len;
	int	i;

	len = 0;
	while (lst != NULL)
	{
		i = 0;
		while (lst->str_buf[i] != '\0')
		{
			if (lst->str_buf[i] == '\n')
			{
				len++;
				return (len);
			}
			len++;
			i++;
		}
		lst = lst->next;
	}
	return (len);
}

void	copy_str(t_list1 *list, char *str)
{
	int	i;
	int	k;

	if (NULL == list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->str_buf[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

t_list1	*ft_lstlast_gnl(t_list1 *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_check(t_list1 *lst)
{
	int	i;

	if (NULL == lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i] && i < BUFFER_SIZE)
		{
			if (lst->str_buf[i] == '\n')
				return (1);
			++i;
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_add_elem(t_list1 **lst, char *buf, int fd)
{
	t_list1	*lst_back;
	t_list1	*lst_new;

	lst_back = ft_lstlast_gnl(lst[fd]);
	lst_new = malloc(sizeof(t_list1));
	if (!lst_new)
		return ;
	if (lst_back == NULL)
		lst[fd] = lst_new;
	else
		lst_back->next = lst_new;
	lst_new->str_buf = buf;
	lst_new->next = NULL;
}
