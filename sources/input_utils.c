/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:24:39 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/12 08:18:32 by bpochlau         ###   ########.fr       */
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

void	ft_cleanup_redirectings(t_vars *vars)
{
	t_prg	*temp;
	t_prg	*last;

	last = NULL;
	temp = vars->p_start;
	while (temp)
	{
		if (temp->oper == '<' || temp->oper == '>')
		{
			if (last == NULL)
				vars->p_start = temp->next;
			else
				last->next = temp->next;
			free(temp->prog);
			free(temp);
			temp = NULL;
		}
		if (temp != NULL)
		{
			last = temp;
			temp = temp->next;
		}
		if (!last)
			temp = vars->p_start;
	}
}
