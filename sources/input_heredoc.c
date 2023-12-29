/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:34:56 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/29 20:35:47 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	ft_exit(vars, OK);
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
