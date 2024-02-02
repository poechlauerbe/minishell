/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_comb_progs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:16:04 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_prog_len(int *count, t_prg *p_prog, t_prg *prog)
{
	char	**temp;

	temp = p_prog->prog;
	while (*temp)
	{
		*count += 1;
		temp += 1;
	}
	temp = prog->prog;
	while (*temp)
	{
		*count += 1;
		temp += 1;
	}
}

void	ft_transfer_prog_str(char **new_prog, char **p_prog, char **prog)
{
	int	i;
	int	j;

	i = 0;
	while (p_prog[i])
	{
		new_prog[i] = p_prog[i];
		i++;
	}
	j = 0;
	while (prog[j])
	{
		new_prog[i] = prog[j];
		i++;
		j++;
	}
}

void	ft_combine(t_vars *vars, t_prg **prog, t_prg *p_prog, t_prg *last)
{
	int		count;
	char	**new_prog;

	count = 0;
	ft_check_prog_len(&count, p_prog, (*prog));
	new_prog = malloc((count + 1) * sizeof(char *));
	if (!new_prog)
		ft_exit(vars, MALLOC_ERROR, 0);
	new_prog[count] = NULL;
	ft_transfer_prog_str(new_prog, p_prog->prog, (*prog)->prog);
	if (p_prog->prog)
		free(p_prog->prog);
	p_prog->prog = new_prog;
	last->next = (*prog)->next;
	if ((*prog)->prog)
		free((*prog)->prog);
	free((*prog));
	*prog = NULL;
}

void	ft_comb_progs(t_vars *vars)
{
	t_prg	*temp;
	t_prg	*p_last;
	t_prg	*last;
	t_prg	*saved;
	int		i;

	i = 0;
	temp = vars->p_start;
	p_last = vars->p_start;
	while (temp)
	{
		saved = temp->next;
		if (temp->oper == '0' && (i++ != 0))
			ft_combine(vars, &temp, p_last, last);
		else if (temp->oper == '|')
			p_last = temp;
		if (i == 1)
			last = temp;
		else if (!temp)
			last = last->next;
		else
			last = temp;
		temp = saved;
	}
}
