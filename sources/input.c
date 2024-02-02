/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:05:10 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/02 15:11:01 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_start_err(t_vars *vars, char *temp, int i, int j)
{
	vars->exit_code = SYNTAX_ERROR;
	vars->no_exec = SYNTAX_ERROR;
	err_handler();
	if (!j)
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%c'\n",
			temp[i]);
	else
		ft_printf_fd(2, "minishell: not handled in minishell`%c'\n", temp[i]);
	err_handle_free();
}

int	ft_start(t_vars *vars)
{
	int		i;
	char	*temp;

	temp = vars->inp;
	i = 0;
	while (temp[i] && (temp[i] == 32 || (temp[i] > 8 && temp[i] < 14)))
		i++;
	if (temp[i] == '|' || temp[i] == '}')
	{
		ft_start_err(vars, temp, i, 0);
		return (SYNTAX_ERROR);
	}
	else if (temp[i] == '{')
	{
		ft_start_err(vars, temp, i, 1);
		return (SYNTAX_ERROR);
	}
	return (OK);
}

void	ft_remove_empty_prog(char **prog, int i)
{
	int	j;

	j = i;
	while (prog[j])
	{
		if (prog[j][0] == '\0')
		{
			free(prog[j]);
			prog[j] = NULL;
			j++;
		}
		else
			prog[i++] = prog[j++];
	}
	prog[i] = NULL;
}

void	ft_check_empty_progs(t_vars *vars)
{
	t_prg	*temp;
	int		i;

	temp = vars->p_start;
	while (temp)
	{
		i = 0;
		while (temp->prog && temp->prog[i])
		{
			if (temp->prog[i][0] == '\0' && temp->prog[i + 1])
				ft_remove_empty_prog(temp->prog, i);
			i++;
		}
		temp = temp->next;
	}
}

void	ft_check_input(t_vars *vars)
{
	if (ft_start(vars))
		return ;
	ft_check_string_count(vars, vars->inp);
	ft_malloc_prog_2d_str(vars, vars->inp);
	ft_cleanup_lst(vars);
	if (ft_check_redirect_file(vars))
		return ;
	ft_comb_progs(vars);
	ft_expand_all_vars(vars);
	ft_red_file(vars, vars->p_start);
	ft_cleanup_reds(vars);
	ft_check_empty_progs(vars);
	ft_quote_remover(vars);
	ft_pipecount(vars);
	ft_add_underscore(vars, vars->p_start->prog);
	if (g_flag != 0)
	{
		vars->no_exec = 130;
		vars->exit_code = 130;
	}
}
