/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:20 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/29 17:06:01 by bpochlau         ###   ########.fr       */
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
			if (!vars.pipe_count && !vars.syntax_err)
			{
				if (ft_builtin_check(&vars, vars.p_start) == NOT_USED)
					ft_pipe(&vars);
			}
			else if (!vars.syntax_err)
				ft_pipe(&vars);
			ft_free_input(&vars);
			vars.syntax_err = OK;
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
