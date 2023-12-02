/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:24:39 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/01 16:38:18 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_new_node(t_vars *vars, t_prg **temp, char **inp)
{
	(*temp)->next = malloc(sizeof(t_prg));
	if (!(*temp)->next)
		ft_exit(vars, MALLOC_ERROR);
	(*temp) = (*temp)->next;
	(*temp)->next = NULL;
	(*temp)->str_c = 0;
	(*temp)->oper = **inp;
	inp++;
}

void	ft_check_quotes(char **inp)
{
	if (**inp == '\'')
	{
		*inp += 1;
		while (**inp != '\'')
			*inp += 1;
	}
	else if (**inp == '\"')
	{
		*inp += 1;
		while (**inp != '\"')
			*inp += 1;
	}
}
