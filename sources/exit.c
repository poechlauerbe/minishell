/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:28:25 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/29 16:32:12 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	err_mes(int errcd)
{
	ft_putstr_fd("Error\n", 2);
	ft_putnbr_fd(errcd, 2);
	ft_putstr_fd("\n", 2);
}



void	ft_free_envv(t_vars *vars)
{
	t_kv	*tmp;

	while (vars->envv)
	{
		tmp = vars->envv->next;
		if (vars->envv->key)
			free (vars->envv->key);
		if (vars->envv->val)
			free (vars->envv->val);
		free (vars->envv);
		vars->envv = tmp;
	}
}

void	ft_exit(t_vars *vars, int errcd)
{
	if (errcd > 256)
		err_mes(errcd);
	// else
	// 	ft_putstr_fd("exit\n", 2);
	ft_free_input(vars);
	ft_free_pipes(vars);
	// ft_free_envv(vars);
	exit(errcd);
}

int	ft_reset(t_vars *vars)
{
	ft_free_input(vars);
	return (1);
}
