/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:24:45 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/29 16:26:06 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_pipes(t_vars *vars)
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
