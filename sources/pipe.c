/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:46:51 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/05 16:44:52 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pipe(t_vars *vars)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	t_prg	*temp;

	temp = vars->p_start;
	if (pipe(fd) == -1)
		return (PIPE_ERROR);
	pid1 = fork();
	if (pid1 < 0)
		return (FORK_ERROR_1);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(temp->prog[0], temp->prog, NULL);
		exit(0);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (FORK_ERROR_2);
	if (pid2 == 0)
	{
		temp = temp->next;
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(temp->prog[0], temp->prog, NULL);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (OK);
}

	// i = 0;
	// while (i < count_pipe && pid[i] != 0)
	// {
	// 	pid[++i] = fork();
	// }
