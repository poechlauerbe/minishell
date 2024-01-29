/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:40:48 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/29 12:20:18 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_flag = 0;

void	ft_minishell_input_handling(t_vars *vars)
{
	add_history(vars->inp);
	ft_check_input(vars);
	if (!vars->pipe_count && !vars->no_exec)
	{
		if (ft_builtin_single_prog(vars, vars->p_start) == NOT_USED)
			ft_pipe(vars);
	}
	else if (!vars->no_exec)
		ft_pipe(vars);
	ft_free_input(vars);
	vars->no_exec = OK;
}

void	ft_minishell_inner_loop(t_vars *vars)
{
	if (g_flag)
		ft_handle_signals();
	vars->inp = readline("$> ");
	if (g_flag)
	{
		vars->exit_code = g_flag;
		g_flag = 0;
	}
	if (!vars->inp)
		ft_exit(vars, vars->exit_code);
	else if (ft_strlen(vars->inp) > 0)
		ft_minishell_input_handling(vars);
	ft_reset(vars);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);
	ft_handle_signals();
	while (1)
		ft_minishell_inner_loop(&vars);
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
// 		else
// 		{
// 			char *line;
// 			line = get_next_line(fileno(stdin));
// 			vars.inp = ft_strtrim(line, "\n");
// 			free(line);
// 		}
// 		if (g_flag)
// 		{
// 			vars.exit_code = g_flag;
// 			g_flag = 0;
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
// 	}
// }
