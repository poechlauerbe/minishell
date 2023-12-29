/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:46:51 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/29 16:53:11 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	ft_pipe_loop(t_vars *vars)
{
	int		fd_r_in;
	int		fd_r_out;
	int		i;
	int		status;
	int		commands;
	t_prg	*temp;
	t_red	*reds;

	commands = vars->pipe_count + 1;
	temp = vars->p_start;
	vars->fd = malloc(vars->pipe_count * 2 * sizeof(int));
	if (!vars->fd)
		ft_exit(vars, MALLOC_ERROR);
	vars->pid = malloc(commands * sizeof(int));
	if (!vars->pid)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	while (++i < vars->pipe_count)
		if (pipe(vars->fd + i * 2) == -1)
			ft_exit(vars, PIPE_ERROR);
	i = -1;
	while (++i < commands)
	{
		vars->pid[i] = fork();
		if (vars->pid[i] < 0)
			ft_exit(vars, FORK_ERROR);
		if (vars->pid[i] == 0)
		{
			if (temp->in_file != NULL)
			{
				reds = temp->in_file;
				while (reds)
				{
					if (ft_check_in_access(reds->file, vars->pid, i) != OK)
						exit(1);
					reds = reds->next;
				}
				reds = temp->in_file;
				while (reds->next && reds->next->file)
					reds = reds->next;
				fd_r_in = open(reds->file, O_RDONLY);
				if (fd_r_in < 0)
					ft_exit(vars, OPEN_FILE_ERROR);
				if (dup2(fd_r_in, STDIN_FILENO) == -1)
					ft_exit(vars, DUP_ERROR);
			}
			else
				if (i != 0)
					if (dup2(vars->fd[2 * i - 2], STDIN_FILENO) == -1)
						ft_exit(vars, DUP_ERROR);
			if (temp->out_file != NULL)
			{
				reds = temp->out_file;
				while (reds)
				{
					if (ft_check_out_access(reds->file, vars->pid, i) != OK)
						exit(1);
					fd_r_out = open(reds->file, O_RDWR | O_TRUNC | O_CREAT, 0644);
					if (fd_r_out == -1)
						ft_exit(vars, OPEN_FILE_ERROR);
					close (fd_r_out);
					reds = reds->next;
				}
				reds = temp->out_file;
				while (reds->next && reds->next->file)
					reds = reds->next;
				fd_r_out = open(reds->file, O_RDWR | O_TRUNC);
				if (fd_r_out == -1)
					ft_exit(vars, OPEN_FILE_ERROR);
				if (dup2(fd_r_out, STDOUT_FILENO) == -1)
					ft_exit(vars, DUP_ERROR);
			}
			else
				if (i != commands - 1)
					if (dup2(vars->fd[2 * i + 1], STDOUT_FILENO) == -1)
						ft_exit(vars, DUP_ERROR);
			ft_close_pipes(vars->pipe_count, vars->fd);
			ft_check_prog(vars, temp);
			ft_free_pipe_fd_and_pid(vars);
			ft_exit(vars, OK);
		}
		temp = temp->next;
	}
	ft_close_pipes(vars->pipe_count, vars->fd);
	i = -1;
	while (++i < commands)
		waitpid(vars->pid[i], &status, 0);
	if (WIFEXITED(status))
		vars->exit_code = WEXITSTATUS(status);
	ft_free_pipe_fd_and_pid(vars);
}
