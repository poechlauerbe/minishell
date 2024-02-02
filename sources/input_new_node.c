/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_new_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:18:18 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init_new_node(t_vars *vars, t_prg **temp)
{
	(*temp)->next = ft_calloc(1, sizeof(t_prg));
	if (!(*temp)->next)
		ft_exit(vars, MALLOC_ERROR, 0);
	(*temp) = (*temp)->next;
	(*temp)->next = NULL;
	(*temp)->str_c = 0;
	(*temp)->in_file = NULL;
	(*temp)->out_file = NULL;
}

void	ft_check_app_hered(char **inp, t_prg **temp)
{
	if (**inp == '<' && inp[0][1] == '<')
	{
		(*temp)->oper = O_HEREDOC;
		*inp += 1;
	}
	else if (**inp == '>' && inp[0][1] == '>')
	{
		(*temp)->oper = O_APP_OUT;
		*inp += 1;
	}
	else
		(*temp)->oper = **inp;
}

void	ft_new_node(t_vars *vars, t_prg **temp, char **inp)
{
	ft_init_new_node(vars, temp);
	if (**inp == '|' || **inp == '<' || **inp == '>')
		ft_check_app_hered(inp, temp);
	else
	{
		(*temp)->oper = '0';
		while (**inp && **inp != '|' && **inp != '<' && **inp != '>'
			&& **inp != ' ' && **inp != '\n' && **inp != '\t'
			&& **inp != '\r' && **inp != '\f' && **inp != '\v')
		{
			(*inp) += 1;
		}
		return ;
	}
	(*inp) += 1;
}
