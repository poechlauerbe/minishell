/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:20:58 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/18 10:33:15 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_n_checker(char *str, int *new_line_mark, int *i)
{
	int	j;

	j = 1;
	while (str[j] == 'n')
		j++;
	if (str[j] == '\0')
	{
		*new_line_mark = 1;
		*i += 1;
	}
	else
		return (1);
	return (OK);
}

void	ft_echo(t_vars *vars, char **str)
{
	int	new_line_mark;
	int	i;

	new_line_mark = 0;
	i = 0;
	if (!str[1])
	{
		write(1, "\n", 1);
		vars->exit_code = OK;
		return ;
	}
	while (str[i + 1] && strncmp(str[i + 1], "-n", 2) == 0)
		if (ft_n_checker(str[i + 1], &new_line_mark, &i))
			break ;
	while (str[++i])
	{
		ft_printf("%s", str[i]);
		if (str[i + 1])
			write(1, " ", 1);
	}
	if (new_line_mark == 0)
		write(1, "\n", 1);
	vars->exit_code = OK;
}
