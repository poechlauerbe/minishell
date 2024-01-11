/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_red_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:05:51 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/11 18:06:22 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_assing_reds(t_vars *vars, t_prg *tmp, t_prg **lst, t_prg *prog)
{
	tmp = *lst;
	while (tmp && tmp->oper != '|')
	{
		if (tmp->oper == '>' || tmp->oper == O_APP_OUT)
			ft_red_new_node(vars, &prog->out_file, tmp->prog[0], tmp->oper);
		else if (tmp->oper == '<' || tmp->oper == O_HEREDOC)
			ft_red_new_node(vars, &prog->in_file, tmp->prog[0], tmp->oper);
		tmp = tmp->next;
	}
	*lst = tmp;
}

void	ft_red_file(t_vars *vars, t_prg *lst)
{
	t_prg	*prog;
	t_prg	*tmp;

	tmp = lst;
	while (lst)
	{
		prog = NULL;
		if (tmp->oper == '|')
		{
			prog = tmp;
			tmp = tmp->next;
			lst = tmp;
		}
		while (tmp && tmp->oper != '|')
		{
			if (tmp->oper == '0' && prog == NULL)
				prog = tmp;
			tmp = tmp->next;
		}
		ft_assing_reds(vars, tmp, &lst, prog);
	}
}
