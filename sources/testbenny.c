/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testbenny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:17:45 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/05 13:52:12 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char *argv[])
{
	int	fd[2];
	if (pipe(fd) == - 1)
		return 1;
}

// int main(int argc, char *argv[])
// {
// 	t_vars	vars;
// 	t_prg	*temp;
// 	int		i;

// 	vars.inp = argv[1];
// 	ft_check_input(&vars);
// 	temp = vars.p_start;
// 	while (temp)
// 	{
// 		printf("oper: %c$\n", temp->oper);
// 		i = -1;
// 		while (temp->prog[++i])
// 			printf("string[%i]: %s\n", i, temp->prog[i]);
// 		printf("\n");
// 		temp = temp->next;
// 	}
// }
