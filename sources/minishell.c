/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:20 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/20 17:49:24 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
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
			if (!vars.pipe_count)
			{
				if (ft_builtin_check(&vars, vars.p_start) == NOT_USED)
					ft_pipe_loop(&vars);
			}
			else
				ft_pipe_loop(&vars);
			ft_free_input(&vars);
		}
		free(vars.inp);
		vars.inp = NULL;
	}
}

/* int	main(int argc, char **argv, char **envp)
{
	int		i = 0;
	char	*curpath;
	char	*test = "cd ..";
	// char	*test = "";
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);
	ft_printf("%s\n", ft_return_val(&vars, "PWD"));
	curpath = (char *)malloc(sizeof(char) * ft_strlen(test) + 1);
	if (!curpath)
		;
	else
	{
		while (*test)
		{
			curpath[i++] = *test;
			test++;
		}
		curpath[i] = '\0';
		vars.inp = curpath;
		ft_check_input(&vars);
		ft_printf("PWD: %s\n", ft_return_val(&vars, "PWD"));
		ft_cd(&vars);
		ft_printf("PWD: %s\n", ft_return_val(&vars, "PWD"));
		ft_cd(&vars);
		ft_printf("PWD: %s\n", ft_return_val(&vars, "PWD"));
	}
	free (curpath);
	ft_exit(&vars, OK);
} */

/* int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);
	vars.inp = "export var";
	ft_check_input(&vars);
	ft_export(&vars);
	ft_exit(&vars, OK);
} */
