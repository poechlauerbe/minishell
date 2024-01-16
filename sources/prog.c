/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:41:52 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/16 14:01:13 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_builtin_check(t_vars *vars, t_prg *prog)
{
	if (!prog->prog || !prog->prog[0] || !prog->prog[0][0])
		return (NOT_USED);
	if (ft_strncmp(prog->prog[0], "exit", 5) == 0)
		ft_exit_prog(vars, prog->prog);
	else if (ft_strncmp(prog->prog[0], "pwd", 4) == 0)
		ft_pwd(vars);
	else if (ft_strncmp(prog->prog[0], "export", 7) == 0)
		ft_export(vars);
	else if (ft_strncmp(prog->prog[0], "echo", 5) == 0)
		ft_echo(vars, prog->prog);
	else if (ft_strncmp(prog->prog[0], "env", 4) == 0)
		ft_env(vars);
	else if (ft_strncmp(prog->prog[0], "unset", 6) == 0)
		ft_unset(vars, prog->prog);
	else if (ft_strncmp(prog->prog[0], "cd", 3) == 0)
		ft_cd(vars);
	else
	{
		if (ft_check_shvar(vars, prog))
			return (NOT_USED);
	}
	return (USED);
}

void	ft_check_prog(t_vars *vars, t_prg *prog)
{
	int		acc_c;

	acc_c = 1;
	if (!prog->prog || !prog->prog[0])
		return ;
	if (prog->prog[0][0] == '\0')
	{
		ft_putstr_fd("Command '' not found\n", 2);
		vars->no_exec = 127;
		vars->exit_code = 127;
		ft_exit(vars, 127);
	}
	if (ft_strncmp(prog->prog[0], "./", 2) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	else if (ft_strncmp(prog->prog[0], "../", 3) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	else if (ft_strncmp(prog->prog[0], "/", 1) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	if (acc_c == NOT_OK)
	{
		ft_prog_not_found(vars, prog);
		vars->exit_code = 127;
		ft_exit(vars, 127);
	}
	else if (acc_c == OK)
		execve(prog->prog[0], prog->prog, vars->envp);
	if (ft_builtin_check(vars, prog) == USED)
		ft_exit(vars, OK);
	ft_check_path(vars, prog);
}
