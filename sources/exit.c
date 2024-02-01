/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:28:25 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/01 12:32:17 by bpochlau         ###   ########.fr       */
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
	if (vars->inp)
		free(vars->inp);
	vars->inp = NULL;
	if (errcd > 256)
		err_mes(errcd);
	ft_free_input(vars);
	ft_free_pipe_fd_and_pid(vars);
	if (vars->envv)
		ft_free_envv(vars);
	if (vars->alloc)
		ft_free_envp(vars->envp);
	ft_close_var_open(vars);
	err_handle_free();
	if (isatty(fileno(stdin)) && vars->pipe_count == 0)
		ft_putstr_fd("exit\n", 2);
	exit(errcd);
}

void	ft_reset(t_vars *vars)
{
	if (vars->inp)
		free(vars->inp);
	vars->inp = NULL;
	vars->no_exec = OK;
	vars->pipe_count = 0;
	err_handle_free();
	ft_free_input(vars);
	ft_free_pipe_fd_and_pid(vars);
	ft_close_var_open(vars);
}

void	ft_err_too_many_args(t_vars *vars)
{
	err_handler();
	ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
	vars->exit_code = 1;
	err_handle_free();
}
