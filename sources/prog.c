/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:41:52 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/16 13:47:27 by bpochlau         ###   ########.fr       */
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

void	ft_no_path(t_vars *vars, t_prg *prog)
{
	char	cwd[1024];
	char	*path;
	char	*c_prog;

	path = ft_strjoin(getcwd(cwd, sizeof(cwd)), "/");
	if (!path)
		ft_exit(vars, MALLOC_ERROR);
	c_prog = ft_strjoin(path, prog->prog[0]);
	free(path);
	if (!c_prog)
		ft_exit(vars, MALLOC_ERROR);
	if (access(c_prog, F_OK | X_OK) == OK)
		execve(c_prog, prog->prog, vars->envp);
	free(c_prog);
	ft_prog_not_found(vars, prog);
	ft_exit(vars, vars->exit_code);
}

void	ft_no_rights(t_vars *vars, char *prog)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	ft_exit(vars, 126);
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
		ft_no_path(vars, prog);
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
		free(dir);
		if (!c_prog)
			ft_exit(vars, MALLOC_ERROR);
		if (access(c_prog, F_OK | X_OK) == OK)
			execve(c_prog, prog->prog, vars->envp);
		else if (access(c_prog, F_OK) == OK)
		{
			ft_no_rights(vars, c_prog);
			free (c_prog);
		}
		else
			free (c_prog);
		if (line[i])
			i++;
	}
	c_prog = ft_strjoin("./", prog->prog[0]);
	if (!c_prog)
		ft_exit(vars, MALLOC_ERROR);
	if (access(c_prog, F_OK | X_OK) == OK)
		execve(c_prog, prog->prog, vars->envp);
	else
		free (c_prog);
	ft_prog_not_found(vars, prog);
}

void	ft_is_dir(t_vars *vars, t_prg *prog)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(prog->prog[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	vars->exit_code = 126;
	ft_exit(vars, 126);
}

void	ft_prog_not_found(t_vars *vars, t_prg *prog)
{
	struct stat fileInfo;

	if (stat(prog->prog[0], &fileInfo) == 0 && (ft_strcmp(prog->prog[0], ".")
			&& ft_strcmp(prog->prog[0], "..")))
	{
		if (S_ISDIR(fileInfo.st_mode))
			ft_is_dir(vars, prog);
		else if (!access(prog->prog[0], F_OK))
			ft_no_rights(vars, prog->prog[0]);
	}
	else
	{
		ft_putstr_fd(prog->prog[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		vars->exit_code = 127;
		ft_exit(vars, 127);
	}
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
