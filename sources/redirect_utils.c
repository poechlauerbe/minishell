/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:23:55 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/08 17:53:04 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cleanup_reds(t_vars *vars)
{
	t_prg	*temp;
	t_prg	*last;
	t_prg	*next;

	temp = vars->p_start;
	last = NULL;
	while (temp)
	{
		next = temp->next;
		if (temp->oper == '<' || temp->oper == '>' || temp->oper == O_APP_OUT)
		{
			if (temp->prog)
				free(temp->prog);
			if (temp == vars->p_start)
				vars->p_start = next;
			else
				last->next = next;
			free(temp);
		}
		else
			last = temp;
		temp = next;
	}
}

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

void	ft_cleanup_lst(t_vars *vars)
{
	t_prg	*temp;

	temp = vars->p_start;
	if (temp->oper == '0' && (!temp->prog || !*temp->prog))
	{
		vars->p_start = temp->next;
		free(temp->prog);
		free(temp);
	}
}
