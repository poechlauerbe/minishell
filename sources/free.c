/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:24:45 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/16 16:55:58 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_pipe_fd_and_pid(t_vars *vars)
{
	if (vars->pid)
	{
		free(vars->pid);
		vars->pid = NULL;
	}
	if (vars->fd)
	{
		free(vars->fd);
		vars->fd = NULL;
	}
}

void	ft_free_reds(t_red **file)
{
	t_red	*temp;
	t_red	*next;

	temp = *file;
	while (temp)
	{
		next = temp->next;
		if (temp->file)
		{
			free(temp->file);
			temp->file = NULL;
		}
		free(temp);
		if (temp == *file)
			*file = NULL;
		temp = next;
	}
}

void	ft_free_t_prg(t_prg *temp)
{
	char	**prog;
	int		i;

	i = 0;
	prog = temp->prog;
	while (prog && prog[i])
	{
		free(prog[i]);
		i++;
	}
	if (prog)
		free(prog);
	if (temp)
		free(temp);
}

void	ft_free_input(t_vars *vars)
{
	t_prg	*temp;
	t_prg	*temp2;

	temp = vars->p_start;
	while (temp)
	{
		temp2 = temp->next;
		if (temp->in_file)
			ft_free_reds(&temp->in_file);
		if (temp->out_file)
			ft_free_reds(&temp->out_file);
		ft_free_t_prg(temp);
		temp = temp2;
	}
	vars->p_start = NULL;
}

void	ft_close_var_open(t_vars *vars)
{
	if (vars->std_out && dup2(vars->std_out, STDOUT_FILENO) == -1)
		ft_exit(vars, DUP_ERROR);
	if (vars->std_out)
	{
		close(vars->std_out);
		vars->std_out = 0;
	}
	if (vars->fd_open_out)
	{
		close(vars->fd_open_out);
		vars->fd_open_out = 0;
	}
	if (vars->std_in && dup2(vars->std_in, STDIN_FILENO) == -1)
		ft_exit(vars, DUP_ERROR);
	if (vars->std_in)
	{
		close(vars->std_in);
		vars->std_in = 0;
	}
	if (vars->fd_open_in)
	{
		close(vars->fd_open_in);
		vars->fd_open_in = 0;
	}
}
