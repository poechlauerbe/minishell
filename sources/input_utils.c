/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:24:39 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/08 20:36:17 by bpochlau         ###   ########.fr       */
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
	(*temp)->in_file = NULL;
	(*temp)->out_file = NULL;
	if ( **inp == '|' || **inp == '<' || **inp == '>')
		(*temp)->oper = **inp;
	else
	{
		(*temp)->oper = '0';
		while (**inp != '|' && **inp != '<' && **inp != '>'
			&& **inp != ' ' && **inp != '\n' && **inp != '\t'
			&& **inp != '\r' && **inp != '\f' && **inp != '\v')
		{
			*inp += 1;
		}
		return ;
	}
	(*inp) += 1;
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
