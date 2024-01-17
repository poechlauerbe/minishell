/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:51:28 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/17 12:52:48 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_dir(t_vars *vars, char *str)
{
	void	*ptr;

	ptr = opendir(str);
	if (!ptr)
		return (OK);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	vars->exit_code = NO_SUCH_FILE_OR_DIRECTORY;
	vars->no_exec = NO_SUCH_FILE_OR_DIRECTORY;
	closedir(ptr);
	return (1);
}

int	ft_check_in_access(char *file, int *pid, int i, t_vars *vars)
{
	int	j;

	if (ft_check_dir(vars, file))
		return (1);
	if (access(file, R_OK) == 0)
		return (OK);
	else
	{
		j = -1;
		while (++j < i)
			waitpid(pid[j], NULL, 0);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
}

int	ft_check_out_access(char *file, int *pid, int i, t_vars *vars)
{
	int	j;

	if (ft_check_dir(vars, file))
		return (1);
	if (access(file, F_OK) != 0 && !ft_check_dir(vars, file))
	{
		if (ft_check_command_path(file, pid, i, vars))
			return (1);
		return (0);
	}
	else
	{
		if (access(file, W_OK) == 0)
			return (OK);
		else
		{
			j = -1;
			while (++j < i)
				waitpid(pid[j], NULL, 0);
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (1);
		}
	}
}
