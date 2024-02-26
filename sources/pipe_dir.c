/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:51:28 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/26 14:38:18 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_dir(t_vars *vars, char *str)
{
	void	*ptr;

	ptr = opendir(str);
	if (!ptr)
		return (OK);
	err_handler();
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	err_handle_free();
	vars->exit_code = NO_SUCH_FILE_OR_DIRECTORY;
	vars->no_exec = NO_SUCH_FILE_OR_DIRECTORY;
	closedir(ptr);
	return (1);
}

int	ft_check_in_access(char *file, t_vars *vars)
{
	if (ft_check_dir(vars, file))
		return (1);
	if (access(file, R_OK) == 0)
		return (OK);
	else
	{
		err_handler();
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		err_handle_free();
		return (1);
	}
}

int	ft_check_out_access(char *file, t_vars *vars)
{
	if (ft_check_dir(vars, file))
		return (1);
	if (access(file, F_OK) != 0 && !ft_check_dir(vars, file))
	{
		if (ft_check_command_path(file, vars))
			return (1);
		return (0);
	}
	else
	{
		if (access(file, W_OK) == 0)
			return (OK);
		else
		{
			err_handler();
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			err_handle_free();
			return (1);
		}
	}
}

int	ft_ambigious(t_red *tmp, t_vars *vars)
{
	int	i;

	i = 0;
	while (tmp->file[i] && (tmp->file[i] == '"' || tmp->file[i] == '\''))
		i++;
	if (!tmp->file[i])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->filename, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		vars->exit_code = 1;
		return (1);
	}
	while (tmp->file[i] && tmp->file[i] != ' ')
		i++;
	if (tmp->file[i])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->filename, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		vars->exit_code = 1;
		return (1);
	}
	return (OK);
}
