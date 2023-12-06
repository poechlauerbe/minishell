/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:46:51 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/06 12:42:40 by bpochlau         ###   ########.fr       */
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
	int		pid;
	int		i;
	t_prg *temp;

	temp = vars->p_start;
	ft_pipecount(vars);
	fd = malloc(vars->pipe_count * 2 * sizeof(int));
	if (!fd)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	while (++i < vars->pipe_count)
		if (pipe(fd + i * 2) == -1)
			ft_exit(vars, PIPE_ERROR);
	i = -1;
	while (++i < vars->pipe_count)
	{
		pid = fork();
		if (pid < 0)
			ft_exit(vars, FORK_ERROR);
		if (pid == 0)
		{
			if (i != vars->pipe_count - 1)
				if (dup2(fd[2 * i + 1], STDOUT_FILENO) == -1)
					ft_exit(vars, DUP_ERROR);
			if (i != 0)
				if (dup2(fd[2 * i - 2], STDIN_FILENO) == -1)
					ft_exit(vars, DUP_ERROR);
			ft_close_pipes(vars->pipe_count, fd);
			execve(temp->prog[0], temp->prog, NULL);
			temp = temp->next;
		}
	}
}

// int	ft_pipe(t_vars *vars)
// {
// 	int		fd[2];
// 	int		pid1;
// 	int		pid2;
// 	t_prg	*temp;

// 	temp = vars->p_start;
// 	if (pipe(fd) == -1)
// 		return (PIPE_ERROR);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		return (FORK_ERROR_1);
// 	if (pid1 == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve(temp->prog[0], temp->prog, NULL);
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		return (FORK_ERROR_2);
// 	if (pid2 == 0)
// 	{
// 		temp = temp->next;
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve(temp->prog[0], temp->prog, NULL);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	if (waitpid(pid1, NULL, 0) == -1)
// 		return (WAITPID_ERROR);
// 	if (waitpid(pid2, NULL, 0) == -1)
// 		return (WAITPID_ERROR);
// 	return (OK);
// }

	// i = 0;
	// while (i < count_pipe && pid[i] != 0)
	// {
	// 	pid[++i] = fork();
	// }
