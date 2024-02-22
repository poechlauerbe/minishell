/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:22:06 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/22 15:57:43 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_builtin_single_prog3(t_vars *vars, t_prg *prog, int errcd)
{
	if (ft_strncmp(prog->prog[0], "unset", 6) == 0)
	{
		errcd = ft_check_files_sp(vars, prog);
		if (errcd == OK)
			ft_unset(vars, prog->prog);
	}
	else if (ft_strncmp(prog->prog[0], "cd", 3) == 0)
	{
		errcd = ft_check_files_sp(vars, prog);
		if (errcd == OK)
			ft_cd(vars);
	}
	else if (ft_check_shvar(vars, prog))
		return (NOT_USED);
	return (USED);
}

int	ft_builtin_single_prog2(t_vars *vars, t_prg *prog, int errcd, int retval)
{
	retval = USED;
	if (ft_strncmp(prog->prog[0], "export", 7) == 0)
	{
		errcd = ft_check_files_sp(vars, prog);
		if (errcd == OK)
			ft_export(vars, vars->p_start->prog);
	}
	else if (ft_strncmp(prog->prog[0], "echo", 5) == 0)
	{
		errcd = ft_check_files_sp(vars, prog);
		if (errcd == OK)
			ft_echo(vars, prog->prog);
	}
	else if (ft_strncmp(prog->prog[0], "env", 4) == 0)
	{
		errcd = ft_check_files_sp(vars, prog);
		if (errcd == OK)
			ft_env(vars);
	}
	else
		retval = ft_builtin_single_prog3(vars, prog, errcd);
	return (retval);
}

int	ft_builtin_single_prog(t_vars *vars, t_prg *prog)
{
	int	errcd;
	int	retval;

	retval = USED;
	errcd = OK;
	if (!prog->prog || !prog->prog[0] || !prog->prog[0][0])
		return (NOT_USED);
	if (ft_strncmp(prog->prog[0], "exit", 5) == 0)
	{
		errcd = ft_check_files_sp(vars, prog);
		if (errcd == OK)
			ft_exit_prog(vars, prog->prog);
	}
	else if (ft_strncmp(prog->prog[0], "pwd", 4) == 0)
	{
		errcd = ft_check_files_sp(vars, prog);
		if (errcd == OK)
			ft_pwd(vars);
	}
	else
		retval = ft_builtin_single_prog2(vars, prog, errcd, retval);
	if (retval == NOT_USED)
		return (NOT_USED);
	ft_close_var_open(vars);
	return (USED);
}
