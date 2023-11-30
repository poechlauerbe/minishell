/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:20 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 17:29:15 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init(t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
}

int	main(void)
{
	int i;
	t_vars	vars;

	ft_init(&vars);
	ft_handle_singals();
	while (1)
	{
		vars.inp = readline("Prompt> $");
		if (!vars.inp)
			(exit(EOF + 128));
		else if(ft_strlen(vars.inp) > 0)
		{
			add_history(vars.inp);
			ft_check_input(&vars);
			ft_printf("%i\n", vars.p_start->oper);
			ft_printf("%i\n", vars.p_start->next->oper);
			ft_printf("%p\n", vars.p_start->next->prog);
			ft_printf("%p\n", vars.p_start->next->prog[0]);
			ft_printf("%sa\n", vars.p_start->next->prog[2]);
			i = 0;
			while (vars.p_start->prog[i])
			{
				printf("%s ", vars.p_start->prog[i]);
				i++;
			}
			ft_printf("%i\n", vars.p_start->str_c);
			ft_free_input(&vars);
		}
		else
		{
			free(vars.inp);
			vars.inp = NULL;
		}
		// if(ft_strcmp(vars.inp, "pwd", 3) == 0)
		// 	printf("%s", getcwd());
		free(vars.inp);
		vars.inp = NULL;
	}
}
