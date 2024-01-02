/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:52:00 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/02 16:24:28 by bpochlau         ###   ########.fr       */
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

int	ft_check_in_access(char *file, int *pid, int i)
{
	int	j;

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

int	ft_check_out_access(char *file, int *pid, int i)
{
	int	j;

	if (access(file, F_OK) != 0)
		return (OK);
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
