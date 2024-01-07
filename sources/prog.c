/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:41:52 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/07 14:03:00 by tbenz            ###   ########.fr       */
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
		ft_unset(vars);
	else if (ft_strncmp(prog->prog[0], "cd", 3) == 0)
		ft_cd(vars);
	else
	{
		if (ft_check_shvar(vars, prog))
			return (NOT_USED);
	}
	// vars->exit_code = OK;
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
	// i think we are missing a free here:
	// else
	// 	free (c_prog);
	ft_prog_not_found(vars, prog);
	// vars->exit_code = 127;
	// exit(127);
}

void	ft_is_dir(t_vars *vars, t_prg *prog, char *nfd)
{
	char	*ndir;
	int		len;

	ndir = "Is a directory\n";
	len = (ft_strlen(prog->prog[0]) * 2) + 4 + ft_strlen(ndir) + 1;
	nfd = calloc(len, sizeof(char));
	if (!nfd)
		ft_exit(vars, MALLOC_ERROR);
	ft_strlcat(nfd, prog->prog[0], ft_strlen(prog->prog[0]) + 1);
	ft_strlcat(nfd, ": ", ft_strlen(prog->prog[0]) + 3);
	ft_strlcat(nfd, nfd, ft_strlen(nfd) * 2 + 1);
	ft_strlcat(nfd, ndir, len);
	ft_printf_fd(2, nfd);
	free(nfd);
	vars->exit_code = 126;
	exit(126);
}

void	ft_prog_not_found(t_vars *vars, t_prg *prog)
{
	char	*nfd;

	nfd = NULL;
	if (!access(prog->prog[0], F_OK) && (ft_strcmp(prog->prog[0], ".")
		&& ft_strcmp(prog->prog[0], "..")))
		ft_is_dir(vars, prog, nfd);
	else
	{
		nfd = ft_strjoin(prog->prog[0], ": command not found\n");
		if (!nfd)
			ft_exit(vars, MALLOC_ERROR);
		ft_printf_fd(2, nfd);
		free (nfd);
		vars->exit_code = 127;
		exit(127);
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
		exit(127);
	}
	else if (acc_c == OK)
		execve(prog->prog[0], prog->prog, vars->envp);
	if (ft_builtin_check(vars, prog) == USED)
		ft_exit(vars, OK);
	ft_check_path(vars, prog);
}
