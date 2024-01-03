/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:34:56 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/03 17:58:20 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_name(t_vars *vars, t_red *red_in)
{
	char	*num_itoa;

	vars->tmp_count++;
	num_itoa = ft_itoa(vars->tmp_count);
	if (!num_itoa)
		ft_exit(vars, MALLOC_ERROR);
	free(red_in->file);
	red_in->file = ft_strjoin("./m_s_h_", num_itoa);
	if (!red_in->file)
		ft_exit(vars, MALLOC_ERROR);
}

void	ft_make_tmp_file(t_vars *vars, t_red *red_in)
{
	int	i;
	int	fd;

	ft_create_name(vars, red_in);
	fd = open(red_in->file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		ft_exit(vars, OPEN_FILE_ERROR);
	i = 0;
	while (red_in->heredoc[i])
	{
		write(fd, &red_in->heredoc[i], 1);
		i++;
	}
	close(fd);
}

void	ft_heredoc_exec(t_vars *vars, t_red *red_in)
{
	char	*str;
	char	*old;
	int		len;

	red_in->heredoc = NULL;
	len = ft_strlen(red_in->file);
	str = get_next_line(0);
	while (ft_strncmp(str, red_in->file, len) != 0)
	{
		old = red_in->heredoc;
		if (!old)
			red_in->heredoc = str;
		else
		{
			red_in->heredoc = ft_strjoin(old, str);
			free(old);
			free(str);
			if (!red_in->heredoc)
				ft_exit(vars, MALLOC_ERROR);
		}
		str = get_next_line(0);
	}
	ft_make_tmp_file(vars, red_in);
}


void	ft_heredoc(t_vars *vars)
{
	t_prg	*prog;
	t_red	*red_in;

	prog = vars->p_start;
	while (prog)
	{
		red_in = prog->in_file;
		while (red_in)
		{
			if (red_in->oper == O_HEREDOC)
				ft_heredoc_exec(vars, red_in);
			red_in = red_in->next;
		}
		prog = prog->next;
	}
}
