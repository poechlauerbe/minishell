/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:41:52 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/16 16:55:21 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_builtin_single_prog(t_vars *vars, t_prg *prog)
{
	t_red	*reds;

	reds = NULL;
	if (prog->in_file != NULL)
		ft_check_input_file(vars, prog, reds, 0);
	if (prog->out_file != NULL)
		ft_check_output_file(vars, prog, reds, 0);
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

int	ft_builtin(t_vars *vars, t_prg *prog)
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

void	ft_check_w_stand_path(t_vars *vars, t_prg *prog)
{
	int		acc_c;

	acc_c = 1;
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
}

void	ft_check_prog(t_vars *vars, t_prg *prog)
{
	if (!prog->prog || !prog->prog[0])
		return ;
	if (prog->prog[0][0] == '\0')
	{
		ft_putstr_fd("Command '' not found\n", 2);
		vars->no_exec = 127;
		vars->exit_code = 127;
		ft_exit(vars, 127);
	}
	ft_check_w_stand_path(vars, prog);
	if (ft_builtin(vars, prog) == USED)
		ft_exit(vars, OK);
	ft_check_path(vars, prog);
}
