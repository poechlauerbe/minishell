/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:23:55 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/08 12:57:19 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_red_new_node(t_vars *vars, t_red **lst, char *file, char oper)
{
	t_red	*new;
	t_red	*temp;

	new = malloc(sizeof(t_red));
	if (!new)
		ft_exit(vars, MALLOC_ERROR);
	new->next = NULL;
	new->file = file;
	new->oper = oper;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
