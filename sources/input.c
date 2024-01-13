/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:05:10 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/12 08:34:42 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		vars->exit_code = SYNTAX_ERROR;
		vars->no_exec = SYNTAX_ERROR;
		ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n",
			temp[i]);
		return (SYNTAX_ERROR);
	}
	else if (temp[i] == '{')
	{
		vars->exit_code = SYNTAX_ERROR;
		vars->no_exec = SYNTAX_ERROR;
		ft_printf_fd(2, "bash: not handled in minishell`%c'\n", temp[i]);
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
	ft_malloc_prog_2d_str(vars);
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
}

	// temp = vars->p_start;
	// while (temp)
	// {
	// 	printf("oper: %c$\n", temp->oper);
	// 	i = -1;
	// 	while (temp->prog[++i])
	// 		printf("string[%i]: %s\n", i, temp->prog[i]);
	// 	printf("\n");
	// 	while(temp->out_file)
	// 	{
	// 		printf("out: %s, %c$\n", temp->out_file->file, temp->out_file->oper);
	// 		temp->out_file = temp->out_file->next;
	// 	}
	// 	while(temp->in_file)
	// 	{
	// 		printf("in: %s, %c$\n", temp->in_file->file, temp->in_file->oper);
	// 		temp->in_file = temp->in_file->next;
	// 	}
	// 	temp = temp->next;
	// }
