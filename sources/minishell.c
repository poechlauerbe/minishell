/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:20 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/11 17:42:53 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);
	ft_handle_signals();
	while (1)
	{
		vars.inp = readline("Prompt> $");
		if (!vars.inp)
			ft_exit(&vars, OK);
		else if (ft_strlen(vars.inp) > 0)
		{
			add_history(vars.inp);
			ft_check_input(&vars);
			// ft_input(&vars);
			if (!vars.pipe_count)
			{
				if (ft_builtin_check(&vars, OK) == NOT_USED)
					ft_pipe_loop(&vars);
			}
			else
				ft_pipe_loop(&vars);
			ft_free_input(&vars);
		}
		free(vars.inp);
		vars.inp = NULL;
	}
} */

	// Thorben test env-key values
int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	// t_kv	*first;

	ft_init(&vars, argc, argv, envp);
	ft_order_envv(&vars);
	ft_add_envv(&vars, "HANS", "eins", 1);
	char *input_new = {"export HANS"};
	vars.inp = input_new;
	printf("%s\n", vars.inp);
	ft_check_input(&vars);
	if (!vars.pipe_count)
	{
		if (ft_builtin_check(&vars, vars.p_start) == NOT_USED)
			ft_pipe_loop(&vars);
	}
	else
		ft_pipe_loop(&vars);
	// ft_free_input(&vars);
	// char *input_new2 = {"export"};
	// vars.inp = input_new2;
	// ft_check_input(&vars);
	// ft_input(&vars);
	ft_exit(&vars, 0);
}
