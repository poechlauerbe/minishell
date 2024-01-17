/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:22:06 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/17 12:08:46 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_builtin_single_prog(t_vars *vars, t_prg *prog)
{
	int	errcd;

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
	else if (ft_strncmp(prog->prog[0], "export", 7) == 0)
	{
		errcd = ft_check_files_sp(vars, prog);
		if (errcd == OK)
			ft_export(vars);
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
	else if (ft_strncmp(prog->prog[0], "unset", 6) == 0)
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
	ft_close_var_open(vars);
	return (USED);
}
