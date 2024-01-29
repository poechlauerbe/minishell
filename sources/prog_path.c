/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:01:04 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/29 11:45:29 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	{
		signal(SIGQUIT, SIG_DFL);
		execve(c_prog, prog->prog, vars->envp);
	}
	free(c_prog);
	ft_prog_not_found(vars, prog);
	ft_exit(vars, vars->exit_code);
}

void	ft_copy_path(int i, int i_start, char *dir, char *line)
{
	int	j;

	j = 0;
	while (j < i - i_start)
	{
		dir[j] = line[i_start + j];
		j++;
	}
	dir[j] = '/';
	dir[j + 1] = '\0';
}

void	ft_check_prog_path(t_vars *vars, t_prg *prog, char *dir)
{
	char	*c_prog;

	c_prog = ft_strjoin(dir, prog->prog[0]);
	free(dir);
	if (!c_prog)
		ft_exit(vars, MALLOC_ERROR);
	if (access(c_prog, F_OK | X_OK) == OK)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(c_prog, prog->prog, vars->envp);
	}
	else if (access(c_prog, F_OK) == OK)
		ft_no_rights(vars, c_prog, c_prog);
	else
		free (c_prog);
}

void	ft_check_current_dir(t_vars *vars, t_prg *prog)
{
	char	*c_prog;

	c_prog = ft_strjoin("./", prog->prog[0]);
	if (!c_prog)
		ft_exit(vars, MALLOC_ERROR);
	if (access(c_prog, F_OK | X_OK) == OK)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(c_prog, prog->prog, vars->envp);
	}
	else
		free (c_prog);
}

void	ft_check_path(t_vars *vars, t_prg *prog)
{
	char	*line;
	char	*dir;
	int		i;
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
		ft_copy_path(i, i_start, dir, line);
		ft_check_prog_path(vars, prog, dir);
		if (line[i])
			i++;
	}
	// ft_check_current_dir(vars, prog);
	ft_prog_not_found(vars, prog);
}
