/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:55:29 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/24 12:45:59 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_heredoc_append(t_vars *vars, t_prg *prog, char **str)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp = ft_strjoin(*str, "\n");
	if (!temp)
	{
		free(str);
		ft_exit(vars, MALLOC_ERROR);
	}
	if (*str)
		free(*str);
	*str = NULL;
	temp2 = ft_strjoin(prog->heredoc, temp);
	if (!temp2)
	{
		free(temp);
		ft_exit(vars, MALLOC_ERROR);
	}
	if (prog->heredoc)
		free(prog->heredoc);
	prog->heredoc = temp2;
	if (temp)
		free (temp);
}

void	ft_add_on_heredoc_str(t_vars *vars, t_prg *prog, char *str)
{
	if (prog->heredoc)
		ft_heredoc_append(vars, prog, &str);
	else
	{
		prog->heredoc = ft_strjoin(str, "\n");
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
