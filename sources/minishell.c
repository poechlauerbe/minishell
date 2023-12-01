/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:20 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/01 11:09:05 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init(t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
}

int	main(void)
{
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
			ft_input(&vars);
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
