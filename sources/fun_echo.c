/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:20:58 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/04 12:36:38 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(char **str)
{
	int	new_line_mark;
	int	i;

	new_line_mark = 0;
	i = 0;
	if (!str[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (strncmp(str[1], "-n", 3) == 0)
	{
		new_line_mark = 1;
		i = 1;
	}
	while (str[++i])
	{
		ft_printf("%s", str[i]);
		if (str[i + 1])
			write(1, " ", 1);
	}
	if (new_line_mark == 0)
		write(1, "\n", 1);
}
