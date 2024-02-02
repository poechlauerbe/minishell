/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_single_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:03:36 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/02 14:06:22 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_c_infile_sp(t_vars *vars, t_prg *temp, t_red *reds)
{
	int		fd_r_in;

	reds = temp->in_file;
	while (reds)
	{
		if (ft_check_in_access(reds->file, vars) != OK)
			return (1);
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
	return (OK);
}

int	ft_c_outfile_sp(t_vars *vars, t_prg *temp, t_red *reds)
{
	int		fd_r_out;

	reds = temp->out_file;
	while (reds)
	{
		if (ft_check_out_access(reds->file, vars) != OK)
			return (1);
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
	return (OK);
}

int	ft_check_files_sp(t_vars *vars, t_prg *prog)
{
	t_red	*reds;
	int		errcd;

	reds = NULL;
	errcd = OK;
	if (prog->in_file != NULL)
		errcd = ft_c_infile_sp(vars, prog, reds);
	if (prog->out_file != NULL && errcd == OK)
		errcd = ft_c_outfile_sp(vars, prog, reds);
	return (errcd);
}
