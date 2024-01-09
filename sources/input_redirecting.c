/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:23:55 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/09 11:32:53 by bpochlau         ###   ########.fr       */
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
		if (temp->oper == '<' || temp->oper == '>' || temp->oper == O_APP_OUT
			|| temp->oper == O_HEREDOC)
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

void	ft_append_new_node(t_red *lst, t_red *new)
{
	t_red	*temp;

	temp = lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_red_new_node(t_vars *vars, t_red **lst, char *file, char oper)
{
	t_red	*new;
	char	*str_wo_q;

	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		ft_exit(vars, MALLOC_ERROR);
	new->next = NULL;
	str_wo_q = ft_create_value(vars, file);
	if (!str_wo_q)
	{
		free(new);
		ft_exit(vars, MALLOC_ERROR);
	}
	free(file);
	new->file = str_wo_q;
	new->oper = oper;
	if (*lst == NULL)
		*lst = new;
	else
		ft_append_new_node(*lst, new);
}

void	ft_cleanup_lst(t_vars *vars)
{
	t_prg	*temp;
	t_prg	*temp2;
	int		flag;

	flag = 0;
	temp = vars->p_start;
	temp2 = vars->p_start->next;
	while (temp2 && temp2->oper != '|')
	{
		if (temp2->oper == '0')
			flag++;
		temp2 = temp2->next;
	}
	if (temp->oper == '0' && (!temp->prog || !*temp->prog) && flag)
	{
		vars->p_start = temp->next;
		free(temp->prog);
		free(temp);
	}
}
