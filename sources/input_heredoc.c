/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:34:56 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/04 12:15:29 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_name(t_vars *vars, t_prg *prog)
{
	char	*num_itoa;

	vars->tmp_count++;
	num_itoa = ft_itoa(vars->tmp_count);
	if (!num_itoa)
		ft_exit(vars, MALLOC_ERROR);
	free(prog->prog[0]);
	prog->prog[0] = ft_strjoin("/tmp/m_s_h_", num_itoa);
	free(num_itoa);
	if (!prog->prog[0])
		ft_exit(vars, MALLOC_ERROR);
}

void	ft_make_tmp_file(t_vars *vars, t_prg *prog)
{
	int	i;
	int	fd;

	ft_create_name(vars, prog);
	fd = open(prog->prog[0], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		ft_exit(vars, OPEN_FILE_ERROR);
	i = 0;
	while (prog->heredoc[i])
	{
		write(fd, &prog->heredoc[i], 1);
		i++;
	}
	close(fd);
}

void	ft_heredoc_exec(t_vars *vars, t_prg *prog)
{
	char	*str;
	char	*old;
	int		len;

	prog->heredoc = NULL;
	len = ft_strlen(prog->prog[0]);
	str = get_next_line(0);
	while (ft_strncmp(str, prog->prog[0], len) != 0)
	{
		old = prog->heredoc;
		if (!old)
			prog->heredoc = str;
		else
		{
			prog->heredoc = ft_strjoin(old, str);
			free(old);
			free(str);
			if (!prog->heredoc)
				ft_exit(vars, MALLOC_ERROR);
		}
		str = get_next_line(0);
	}
	ft_make_tmp_file(vars, prog);
}


void	ft_heredoc(t_vars *vars)
{
	t_prg	*prog;

	prog = vars->p_start;
	while (prog)
	{
		if (prog->oper == O_HEREDOC)
			ft_heredoc_exec(vars, prog);
		prog = prog->next;
	}
}
