/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:52:00 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/23 17:45:21 by bpochlau         ###   ########.fr       */
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
				ft_putstr_fd("bash: syntax error near unexpected token `|'", 2);
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
		if (i % 2)
			write(fd[i], "\0", 1);
		close(fd[i]);
	}
}

int	ft_path_checker(char *file, int *pid, t_count *num, t_vars *vars)
{
	char	*test_path;
	int		k;

	test_path = ft_strdup(file);
	if (!test_path)
		ft_exit(vars, MALLOC_ERROR);
	test_path[num->j] = '\0';
	if (access(file, F_OK) == 0)
		return (OK);
	else
	{
		k = -1;
		while (++k < num->i)
			waitpid(pid[k], NULL, 0);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (OK);
}

int	ft_check_command_path(char *file, int *pid, int i, t_vars *vars)
{
	t_count	num;

	num.j = 0;
	while (file[num.j] == '.' || file[num.j] == '/')
		num.j++;
	while (file[num.j])
	{
		num.i = i;
		if (file[num.j] == '/' && ft_path_checker(file, pid, &num, vars))
			return (1);
		num.j++;
	}
	return (OK);
}
