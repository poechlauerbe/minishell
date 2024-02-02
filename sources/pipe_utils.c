/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:52:00 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pipecount(t_vars *vars)
{
	t_prg	*temp;
	int		count;

	count = 0;
	temp = vars->p_start;
	while (temp)
	{
		if (temp->oper == O_PIPE)
		{
			count++;
			if (!temp->in_file && !temp->out_file && !temp->prog[0])
			{
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				ft_putstr_fd("minishell: syntax error ", 2);
				ft_putstr_fd("near unexpected token `|'\n", 2);
				return ;
			}
		}
		temp = temp->next;
	}
	vars->pipe_count = count;
}

void	ft_close_pipes(int pipe_nr, int *fd)
{
	int	i;

	pipe_nr *= 2;
	i = -1;
	while (++i < pipe_nr)
	{
		close(fd[i]);
	}
}

int	ft_path_checker(char *file, t_count *num, t_vars *vars)
{
	char	*test_path;

	test_path = ft_strdup(file);
	if (!test_path)
		ft_exit(vars, MALLOC_ERROR, 0);
	test_path[num->j] = '\0';
	if (access(file, F_OK) == 0)
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
	return (OK);
}

int	ft_check_command_path(char *file, t_vars *vars)
{
	t_count	num;

	num.j = 0;
	while (file[num.j] == '.' || file[num.j] == '/')
		num.j++;
	while (file[num.j])
	{
		if (file[num.j] == '/' && ft_path_checker(file, &num, vars))
			return (1);
		num.j++;
	}
	return (OK);
}

void	ft_wait_childs(t_vars *vars, int commands)
{
	int		i;
	int		status;

	i = -1;
	while (++i < commands)
		waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		vars->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 13)
			vars->exit_code = WEXITSTATUS(status);
		else
			vars->exit_code = 128 + WTERMSIG(status);
		if (vars->exit_code == 139)
			ft_putstr_fd("Segmentation fault (core dumped)\n", 2);
		if (vars->exit_code == 128 + SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		if (vars->exit_code == 130)
			write(1, "\n", 1);
	}
}
