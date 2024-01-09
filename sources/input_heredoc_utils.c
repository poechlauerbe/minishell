/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:55:29 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/09 11:03:39 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_heredoc_append(t_vars *vars, t_prg *prog, char *str)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(prog->heredoc);
	if (!temp)
	{
		free(str);
		ft_exit(vars, MALLOC_ERROR);
	}
	free(prog->heredoc);
	prog->heredoc = ft_strjoin(temp, str);
	if (!prog->heredoc)
	{
		free(temp);
		free(str);
		ft_exit(vars, MALLOC_ERROR);
	}
	free (temp);
}

void	ft_add_on_heredoc_str(t_vars *vars, t_prg *prog, char *str)
{
	if (prog->heredoc)
		ft_heredoc_append(vars, prog, str);
	else
	{
		prog->heredoc = ft_strdup(str);
		if (!prog->heredoc)
		{
			free(str);
			ft_exit(vars, MALLOC_ERROR);
		}
	}
	if (str)
		free (str);
	str = NULL;
}
