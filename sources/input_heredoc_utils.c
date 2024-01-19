/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:55:29 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/19 13:18:05 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_heredoc_append(t_vars *vars, t_red *reds, char *str)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(str, "\n");
	if (!temp)
	{
		free(str);
		ft_exit(vars, MALLOC_ERROR);
	}
	free(str);
	str = ft_strjoin(reds->heredoc, temp);
	if (!str)
	{
		free(temp);
		ft_exit(vars, MALLOC_ERROR);
	}
	if (reds->heredoc)
		free(reds->heredoc);
	reds->heredoc = str;
	free (temp);
}

void	ft_add_on_heredoc_str(t_vars *vars, t_red *reds, char *str)
{
	if (reds->heredoc)
		ft_heredoc_append(vars, reds, str);
	else
	{
		reds->heredoc = ft_strjoin(str, "\n");
		if (!reds->heredoc)
		{
			free(str);
			ft_exit(vars, MALLOC_ERROR);
		}
		if (str)
			free (str);
	}
}
