/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:20:58 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/30 21:15:33 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_vars *vars, char **str)
{
	int	new_line_mark;
	int	i;
	char *str_wo_q;

	str_wo_q = NULL;
	new_line_mark = 0;
	i = 0;
	if (!str[1])
	{
		write(1, "\n", 1);
		vars->exit_code = OK;
		return ;
	}
	if (strncmp(str[1], "-n", 3) == 0)
	{
		new_line_mark = 1;
		i = 1;
	}
	while (str[++i])
	{
		str_wo_q = ft_create_value(vars, str[i]);
		if (!str_wo_q)
			ft_exit(vars, MALLOC_ERROR);
		ft_printf("%s", str_wo_q);
		free(str_wo_q);
		if (str[i + 1])
			write(1, " ", 1);
	}
	if (new_line_mark == 0)
		write(1, "\n", 1);
	vars->exit_code = OK;
}
