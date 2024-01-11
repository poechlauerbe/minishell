/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/01/11 17:52:00 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_red_file(t_vars *vars, t_prg *lst)
{
	t_prg	*prog;
	t_prg	*temp;

	temp = lst;
	while (lst)
	{
		prog = NULL;
		if (temp->oper == '|')
		{
			prog = temp;
			temp = temp->next;
			lst = temp;
		}
		while (temp && temp->oper != '|')
		{
			if (temp->oper == '0')
			{
				if (prog == NULL)
					prog = temp;
			}
			temp = temp->next;
		}
		temp = lst;
		while (temp && temp->oper != '|')
		{
			if (temp->oper == '>' || temp->oper == O_APP_OUT)
				ft_red_new_node(vars, &prog->out_file, temp->prog[0], temp->oper);
			else if (temp->oper == '<')
				ft_red_new_node(vars, &prog->in_file, temp->prog[0], temp->oper);
			else if (temp->oper == O_HEREDOC)
				ft_red_new_node(vars, &prog->in_file, temp->prog[0], temp->oper);
			temp = temp->next;
		}
		lst = temp;
	}
}

int	ft_check_redirect_file(t_vars *vars)
{
	t_prg	*temp;

	temp = vars->p_start;
	while (temp)
	{
		if (temp->oper == '<' || temp->oper == '>' || temp->oper == O_APP_OUT || temp->oper == O_HEREDOC)
		{
			if (!temp->prog[0] && !temp->next)
			{
				ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n");
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				return (SYNTAX_ERROR);
			}
			else if (!temp->prog[0] && (temp->next->oper == '<' || temp->next->oper == '>'))
			{
				ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n", temp->next->oper);
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				return (SYNTAX_ERROR);
			}
			else if (!temp->prog[0] && (temp->next->oper == O_APP_OUT || temp->next->oper == O_HEREDOC))
			{
				if (temp->next->oper == O_HEREDOC && !temp->next->prog[0] && temp->next->next && (temp->next->next->oper == '<' || temp->next->next->oper == O_HEREDOC))
					ft_printf_fd(2, "bash: syntax error near unexpected token `<<<'\n");
				else if (temp->next->oper == O_APP_OUT)
					ft_printf_fd(2, "bash: syntax error near unexpected token `>>'\n");
				else
					ft_printf_fd(2, "bash: syntax error near unexpected token `<<'\n");
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				return (SYNTAX_ERROR);
			}
			else if (!temp->prog[0] && temp->next && temp->next->oper == '|')
			{
				ft_printf_fd(2, "bash: syntax error near unexpected token `|'\n");
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				return (SYNTAX_ERROR);
			}
			else if (temp->oper == O_HEREDOC && temp->prog[0])
				ft_heredoc_exec(vars, temp);
		}
		temp = temp->next;
	}
	return (OK);
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

void	ft_quote_remover(t_vars *vars)
{
	t_prg	*temp;
	int		i;
	char	*str_wo_q;

	temp = vars->p_start;
	while (temp)
	{
		i = -1;
		while (temp->prog[++i])
		{
			str_wo_q = ft_create_value(vars, temp->prog[i]);
			if (!str_wo_q)
				ft_exit(vars, MALLOC_ERROR);
			free(temp->prog[i]);
			temp->prog[i] = str_wo_q;
		}
		temp = temp->next;
	}
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
