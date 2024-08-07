/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:46:51 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/29 11:34:56 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_input_file(t_vars *vars, t_prg *temp, t_red *reds)
{
	int		fd_r_in;

	reds = temp->in_file;
	while (reds)
	{
		if (ft_ambigious(reds, vars))
			ft_exit(vars, 1, 0);
		if (ft_check_in_access(reds->file, vars) != OK)
			ft_exit(vars, 1, 0);
		reds = reds->next;
	}
	reds = temp->in_file;
	while (reds->next && reds->next->file)
		reds = reds->next;
	fd_r_in = open(reds->file, O_RDONLY);
	if (fd_r_in < 0)
		ft_exit(vars, OPEN_FILE_ERROR, 0);
	vars->fd_open_in = fd_r_in;
	vars->std_in = dup(STDIN_FILENO);
	if (dup2(fd_r_in, STDIN_FILENO) == -1)
		ft_exit(vars, DUP_ERROR, 0);
}

void	ft_check_output_file(t_vars *vars, t_prg *temp, t_red *reds)
{
	int		fd_r_out;

	reds = temp->out_file;
	while (reds)
	{
		if (ft_ambigious(reds, vars))
			ft_exit(vars, 1, 0);
		if (ft_check_out_access(reds->file, vars) != OK)
			ft_exit(vars, 1, 0);
		if (reds->oper == O_RED_OUTPUT)
			fd_r_out = open(reds->file, O_RDWR | O_TRUNC | O_CREAT, 0644);
		else
			fd_r_out = open(reds->file, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd_r_out == -1)
			ft_exit(vars, MALLOC_ERROR, 0);
		if (reds->next)
			close (fd_r_out);
		reds = reds->next;
	}
	vars->fd_open_out = fd_r_out;
	vars->std_out = dup(STDOUT_FILENO);
	if (dup2(fd_r_out, STDOUT_FILENO) == -1)
		ft_exit(vars, DUP_ERROR, 0);
}

void	ft_child_process(t_vars *vars, int commands, t_prg *temp, int i)
{
	t_red	*reds;

	signal(SIGINT, SIG_DFL);
	reds = NULL;
	if (temp->in_file != NULL)
		ft_check_input_file(vars, temp, reds);
	else if (i != 0 && dup2(vars->fd[2 * i - 2], STDIN_FILENO) == -1)
		ft_exit(vars, DUP_ERROR, 0);
	if (temp->out_file != NULL)
		ft_check_output_file(vars, temp, reds);
	else if (i != --commands && dup2(vars->fd[2 * i + 1], STDOUT_FILENO) == -1)
		ft_exit(vars, DUP_ERROR, 0);
	ft_close_pipes(vars->pipe_count, vars->fd);
	ft_check_prog(vars, temp);
	ft_free_pipe_fd_and_pid(vars);
	ft_exit(vars, vars->exit_code, 0);
}

void	ft_pipe_loop(t_vars *vars, int commands)
{
	int		i;
	t_prg	*temp;

	signal(SIGINT, ft_handler_remove);
	temp = vars->p_start;
	i = -1;
	while (++i < commands)
	{
		vars->pid[i] = fork();
		if (vars->pid[i] < 0)
			ft_exit(vars, FORK_ERROR, 0);
		if (vars->pid[i] == 0)
			ft_child_process(vars, commands, temp, i);
		temp = temp->next;
	}
	ft_close_pipes(vars->pipe_count, vars->fd);
}

void	ft_pipe(t_vars *vars)
{
	int		i;
	int		commands;

	commands = vars->pipe_count + 1;
	vars->fd = malloc(vars->pipe_count * 2 * sizeof(int));
	if (!vars->fd)
		ft_exit(vars, MALLOC_ERROR, 0);
	vars->pid = malloc(commands * sizeof(int));
	if (!vars->pid)
		ft_exit(vars, MALLOC_ERROR, 0);
	i = -1;
	while (++i < vars->pipe_count)
		if (pipe(vars->fd + i * 2) == -1)
			ft_exit(vars, PIPE_ERROR, 0);
	ft_pipe_loop(vars, commands);
	ft_wait_childs(vars, commands);
	signal(SIGINT, ft_handler_s);
	ft_free_pipe_fd_and_pid(vars);
}
