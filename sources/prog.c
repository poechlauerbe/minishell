/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:41:52 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/11 15:00:02 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_builtin_check(t_vars *vars, t_prg *prog)
{
	if (ft_strncmp(prog->prog[0], "exit", 4) == 0)
		ft_exit(vars, OK);
	else if (ft_strncmp(prog->prog[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(prog->prog[0], "export", 6) == 0)
		ft_export(vars);
	else if (ft_strncmp(prog->prog[0], "echo", 4) == 0)
		ft_echo(prog->prog);
	else if (ft_strncmp(prog->prog[0], "env", 3) == 0)
		ft_env(vars);
	else if (ft_strncmp(prog->prog[0], "unset", 5) == 0)
		ft_unset(vars);
	else
		return (NOT_USED);
	return (USED);
}

void	ft_check_prog(t_vars *vars, t_prg *prog)
{
	int	acc_c;

	acc_c = 1;
	if (ft_strncmp(prog->prog[0], "./", 2) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	else if (ft_strncmp(prog->prog[0], "../", 3) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	else if (ft_strncmp(prog->prog[0], "/", 1) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	if (acc_c == NOT_OK)
	{
		ft_printf_fd(2, "%s: command not found\n", prog->prog[0]);
		exit(127);
	}
	else if (acc_c == OK)
		execve(prog->prog[0], prog->prog, NULL);
	if (ft_builtin_check(vars, prog) == USED)
		ft_exit(vars, OK);
}
