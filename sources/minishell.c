/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:20 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 17:21:49 by tbenz            ###   ########.fr       */
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
		else if (ft_strlen(vars.inp) > 0)
		{
			add_history(vars.inp);
			ft_check_input(&vars);
			ft_free_input(&vars);
		}
		free(vars.inp);
		vars.inp = NULL;
	}
}
