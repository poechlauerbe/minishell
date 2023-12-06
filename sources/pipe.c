/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:46:51 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/06 15:51:02 by bpochlau         ###   ########.fr       */
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
			count++;
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
		close(fd[i]);
}

void	ft_pipe_loop(t_vars *vars)
{
	int		*fd;
	int		*pid;
	int		i;
	// int		status;
	int		commands;
	t_prg *temp;

	ft_pipecount(vars);
	commands = vars->pipe_count + 1;
	temp = vars->p_start;
	fd = malloc(vars->pipe_count * 2 * sizeof(int));
	if (!fd)
		ft_exit(vars, MALLOC_ERROR);
	pid = malloc(commands * sizeof(int));
	if (!pid)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	while (++i < vars->pipe_count)
		if (pipe(fd + i * 2) == -1)
			ft_exit(vars, PIPE_ERROR);
	i = -1;
	while (++i < commands)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			ft_exit(vars, FORK_ERROR);
		if (pid[i] == 0)
		{
			if (i != commands - 1)
				if (dup2(fd[2 * i + 1], STDOUT_FILENO) == -1)
					ft_exit(vars, DUP_ERROR);
			if (i != 0)
				if (dup2(fd[2 * i - 2], STDIN_FILENO) == -1)
					ft_exit(vars, DUP_ERROR);
			ft_close_pipes(vars->pipe_count, fd);
			execve(temp->prog[0], temp->prog, NULL);
		}
		temp = temp->next;
	}
	ft_close_pipes(vars->pipe_count, fd);
	i = -1;
	while (++i < commands)
		waitpid(pid[i], NULL, 0);
	free(pid);
	free(fd);
}
