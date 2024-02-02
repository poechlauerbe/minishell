/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:23:55 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/02 16:07:35 by bpochlau         ###   ########.fr       */
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

void	ft_red_new_node(t_vars *vars, t_red **lst, t_prg *tmp)
{
	t_red	*new;
	char	*str_wo_q;

	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		ft_exit(vars, MALLOC_ERROR, 0);
	new->next = NULL;
	str_wo_q = ft_create_value(vars, tmp->prog[0]);
	if (!str_wo_q)
	{
		free(new);
		ft_exit(vars, MALLOC_ERROR, 0);
	}
	free(tmp->prog[0]);
	tmp->prog[0] = NULL;
	new->file = str_wo_q;
	new->oper = tmp->oper;
	new->filename = tmp->filename;
	if (!(*lst))
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

// void	ft_free(void **ptr)
// {
// 	if (*ptr)
// 		free(*ptr);
// 	*ptr = NULL;
// }

// void	ft_cleanup_redirectings(t_vars *vars)
// {
// 	t_prg	*temp;
// 	t_prg	*last;

// 	last = NULL;
// 	temp = vars->p_start;
// 	while (temp)
// 	{
// 		if (temp->oper == '<' || temp->oper == '>')
// 		{
// 			if (last == NULL)
// 				vars->p_start = temp->next;
// 			else
// 				last->next = temp->next;
// 			ft_free((void **)&temp->filename);
// 			ft_free((void **)temp->prog);
// 			ft_free((void **)&temp);
// 			ft_putstr_fd("\n\ntest\n\n", 2);
// 		}
// 		if (temp != NULL)
// 		{
// 			last = temp;
// 			temp = temp->next;
// 		}
// 		if (!last)
// 			temp = vars->p_start;
// 	}
// }
