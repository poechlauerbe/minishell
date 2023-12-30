/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:41:52 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/30 13:02:11 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_builtin_check(t_vars *vars, t_prg *prog)
{
	if (!prog->prog || !prog->prog[0] || !prog->prog[0][0])
		return (NOT_USED);
	if (ft_strncmp(prog->prog[0], "exit", 5) == 0)
		ft_exit(vars, OK);
	else if (ft_strncmp(prog->prog[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(prog->prog[0], "export", 7) == 0)
		ft_export(vars);
	else if (ft_strncmp(prog->prog[0], "echo", 5) == 0)
		ft_echo(vars, prog->prog);
	else if (ft_strncmp(prog->prog[0], "env", 4) == 0)
		ft_env(vars);
	else if (ft_strncmp(prog->prog[0], "unset", 6) == 0)
		ft_unset(vars);
	else if (ft_strncmp(prog->prog[0], "cd", 3) == 0)
		ft_cd(vars);
	else
	{
		if (ft_check_shvar(vars, prog))
			return (NOT_USED);
	}
	vars->exit_code = OK;
	return (USED);
}

void	ft_check_path(t_vars *vars, t_prg *prog)
{
	char	*line;
	char	*dir;
	char	*c_prog;
	int		i;
	int		j;
	int		i_start;

	line = ft_return_val(vars, "PATH");
	if (!line)
		exit(NOT_DEFINED);
	i = 0;
	while (line[i])
	{
		i_start = i;
		while (line && line[i] != ':' && line[i] != '\0')
			i++;
		dir = malloc((i - i_start + 2) * sizeof(char));
		if (!dir)
			ft_exit(vars, MALLOC_ERROR);
		j = 0;
		while (j < i - i_start)
		{
			dir[j] = line[i_start + j];
			j++;
		}
		dir[j] = '/';
		dir[j + 1] = '\0';
		c_prog = ft_strjoin(dir, prog->prog[0]);
		if (!c_prog)
			ft_exit(vars, MALLOC_ERROR);
		free(dir);
		if (access(c_prog, F_OK | X_OK) == OK)
			execve(c_prog, prog->prog, vars->envp);
		if (line[i])
			i++;
	}
	ft_printf_fd(2, "%s: command not found\n", prog->prog[0]);
	vars->exit_code = 127;
	exit(127);
}

void	ft_check_prog(t_vars *vars, t_prg *prog)
{
	int	acc_c;

	acc_c = 1;
	if (!prog->prog || !prog->prog[0] || !prog->prog[0][0])
		return ;
	if (ft_strncmp(prog->prog[0], "./", 2) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	else if (ft_strncmp(prog->prog[0], "../", 3) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	else if (ft_strncmp(prog->prog[0], "/", 1) == 0)
		acc_c = access(prog->prog[0], F_OK | X_OK);
	if (acc_c == NOT_OK)
	{
		ft_printf_fd(2, "%s: command not found\n", prog->prog[0]);
		vars->exit_code = 127;
		exit(127);
	}
	else if (acc_c == OK)
		execve(prog->prog[0], prog->prog, NULL);
	if (ft_builtin_check(vars, prog) == USED)
		ft_exit(vars, OK);
	ft_check_path(vars, prog);
}
