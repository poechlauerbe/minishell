/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:24:39 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/12 09:11:58 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_quotes(char **inp)
{
	if (**inp == '\'')
	{
		*inp += 1;
		while (**inp && **inp != '\'')
			*inp += 1;
	}
	else if (**inp == '\"')
	{
		*inp += 1;
		while (**inp && **inp != '\"')
			*inp += 1;
	}
}

void	ft_quote_remover(t_vars *vars)
{
	t_prg	*temp;
	int		i;
	char	*str_wo_q;

	temp = vars->p_start;
	while (temp)
	{
		i = -1;
		while (temp->prog[++i])
		{
			str_wo_q = ft_create_value(vars, temp->prog[i]);
			if (!str_wo_q)
				ft_exit(vars, MALLOC_ERROR);
			free(temp->prog[i]);
			temp->prog[i] = str_wo_q;
		}
		temp = temp->next;
	}
}
