/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:28:25 by bpochlau          #+#    #+#             */
/*   Updated: 2023/11/30 17:21:36 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	err_mes(void)
{
	ft_putstr_fd("Error\n", 2);
}

void	ft_free_input(t_vars *vars)
{
	t_prg	*temp;
	t_prg	*temp2;
	char	**prog;
	int		i;

	temp = vars->p_start;
	while (temp)
	{
		prog = temp->prog;
		temp2 = temp->next;
		i = 0;
		while (prog[i])
		{
			free(prog[i]);
			i++;
		}
		free(prog);
		free(temp);
		temp = temp2;
	}
	vars->p_start = NULL;
}

void	ft_exit(t_vars *vars, int errcd)
{
	if (errcd != OK)
		err_mes();
	ft_free_input(vars);
	exit(errcd);
}

int	ft_reset(t_vars *vars)
{
	ft_free_input(vars);
	return (1);
}
