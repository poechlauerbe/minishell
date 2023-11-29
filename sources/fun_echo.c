/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:20:58 by bpochlau          #+#    #+#             */
/*   Updated: 2023/11/29 14:31:00 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(char *str, char *option)
{
	while (str)
	{
		write(1, str, 1);
	}
	if (option == NULL)
		write(1, "\n", 1);
	else if (*option == "n")
		;

}
