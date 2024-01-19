/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/01/19 12:38:36 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_flag = 0;

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	// char	*line;

	ft_init(&vars, argc, argv, envp);
	ft_handle_signals();
	while (1)
	{
		if (g_flag)
			ft_handle_signals();
		if (isatty(fileno(stdin)))
		vars.inp = readline("$>");
		// else
		// {
		// 	line = get_next_line(fileno(stdin));
		// 	vars.inp = ft_strtrim(line, "\n");
		// 	free(line);
		// }
		if (g_flag)
		{
			vars.exit_code = g_flag;
			g_flag = 0;
		}
		if (!vars.inp)
			ft_exit(&vars, vars.exit_code);
		else if (ft_strlen(vars.inp) > 0)
		{
			add_history(vars.inp);
			ft_check_input(&vars);
			if (!vars.pipe_count && !vars.no_exec)
			{
				if (ft_builtin_single_prog(&vars, vars.p_start) == NOT_USED)
					ft_pipe(&vars);
			}
			else if (!vars.no_exec)
				ft_pipe(&vars);
			ft_free_input(&vars);
			vars.no_exec = OK;
		}
		free(vars.inp);
		vars.inp = NULL;
		g_flag = 0;
	}
}

// FOR TESTER:
/* int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);
	ft_handle_signals();
	while (1)
	{
		if (isatty(fileno(stdin)))
			vars.inp = readline("$>");
		if (g_flag)
		{
			vars.exit_code = g_flag;
			g_flag = 0;
		}
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			vars.inp = ft_strtrim(line, "\n");
			free(line);
		}
		if (!vars.inp)
			ft_exit(&vars, vars.exit_code);
		else if (ft_strlen(vars.inp) > 0)
		{
			// add_history(vars.inp);
			ft_check_input(&vars);
			if (!vars.pipe_count && !vars.no_exec)
			{
				if (ft_builtin_single_prog(&vars, vars.p_start) == NOT_USED)
					ft_pipe(&vars);
			}
			else if (!vars.no_exec)
				ft_pipe(&vars);
			ft_free_input(&vars);
			vars.no_exec = OK;
		}
		free(vars.inp);
		vars.inp = NULL;
	}
}

// FOR TESTER:
// int	main(int argc, char **argv, char **envp)
// {
// 	t_vars	vars;

// 	ft_init(&vars, argc, argv, envp);
// 	ft_handle_signals();
// 	while (1)
// 	{
// 		if (isatty(fileno(stdin)))
// 			vars.inp = readline("$>");
// 		if (g_flag)
// 		{
// 			vars.exit_code = g_flag;
// 			g_flag = 0;
// 		}
// 		else
// 		{
// 			char *line;
// 			line = get_next_line(fileno(stdin));
// 			vars.inp = ft_strtrim(line, "\n");
// 			free(line);
// 		}
// 		if (!vars.inp)
// 			ft_exit(&vars, vars.exit_code);
// 		else if (ft_strlen(vars.inp) > 0)
// 		{
// 			// add_history(vars.inp);
// 			ft_check_input(&vars);
// 			if (!vars.pipe_count && !vars.no_exec)
// 			{
// 				if (ft_builtin_single_prog(&vars, vars.p_start) == NOT_USED)
// 					ft_pipe(&vars);
// 			}
// 			else if (!vars.no_exec)
// 				ft_pipe(&vars);
// 			ft_free_input(&vars);
// 			vars.no_exec = OK;
// 		}
// 		free(vars.inp);
// 		vars.inp = NULL;
// 		g_flag = 0;
// 	}
// }

/* int	main(int argc, char **argv, char **envp)
{
	int		i = 0;
	char	*curpath;
	char	*test = "cd '/nfs/homes/tbenz/Desktop/42 Core Curriculum'";
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
