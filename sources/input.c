/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:30:48 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/30 21:19:02 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_string_count(t_vars *vars, char *inp)
{
	t_prg	*temp;

	vars->p_start = malloc(sizeof(t_prg));
	if (!vars->p_start)
		ft_exit(vars, MALLOC_ERROR);
	vars->p_start->next = NULL;
	vars->p_start->oper = '0';
	temp = vars->p_start;
	temp->str_c = 0;
	temp->in_file = NULL;
	temp->out_file = NULL;
	while (*inp)
	{
		while (*inp == ' ' || *inp == '\n' || *inp == '\t'
			|| *inp == '\r' || *inp == '\f' || *inp == '\v')
			inp++;
		if ((*inp >= 33 || *inp < 0) && *inp != 127 && *inp != '|' && *inp != '<' && *inp != '>')
		{
			if ((temp->oper == '<' || temp->oper == '>' || temp->oper == O_APP_OUT) && temp->str_c == 1)
				ft_new_node(vars, &temp, &inp);
			temp->str_c += 1;
		}
		while ((*inp >= 33 || *inp < 0) && *inp != 127)
		{
			if (*inp == '\'' || *inp == '\"')
				ft_check_quotes(&inp);
			if (*inp == '|' || *inp == '<' || *inp == '>')
			{
				ft_new_node(vars, &temp, &inp);
				break ;
			}
			inp++;
		}
	}
}

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
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = vars->inp;
	while (temp && temp[i])
	{
		if (temp[i] == '<' || temp[i] == '>')
		{
			j = i + 1;
			if (temp[j] && temp[i] == temp[j])
				j++;
			while (temp[j] && (temp[j] == 32 || (temp[j] > 8 && temp[j] < 14)))
				j++;
			if (!temp[j])
			{
				ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n");
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				return (SYNTAX_ERROR);
			}
			else if ((temp[j] == '<' || temp[j] == '>')
				&& (temp[j + 1] != '<' && temp[j + 1] != '>'))
			{
				ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n", temp[j]);
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				return (SYNTAX_ERROR);
			}
			else if (ft_strncmp(&temp[j], "<<<", 3) == 0)
			{
				ft_printf_fd(2, "bash: syntax error near unexpected token `<<<'\n");
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				return (SYNTAX_ERROR);
			}
			else if ((temp[j] == '<' || temp[j] == '>')
				&& (temp[j + 1] == '<' || temp[j + 1] == '>'))
			{
				ft_printf_fd(2, "bash: syntax error near unexpected token `%c%c'\n", temp[j], temp[j + 1]);
				vars->no_exec = SYNTAX_ERROR;
				vars->exit_code = SYNTAX_ERROR;
				return (SYNTAX_ERROR);
			}
			else
			{
				while (temp[j] && (temp[j] == 32 || (temp[j] > 8 && temp[j] < 14)))
					j++;
				if (temp[j] == '|')
				{
					ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n", 	temp[j]);
					vars->no_exec = SYNTAX_ERROR;
					vars->exit_code = SYNTAX_ERROR;
					return (SYNTAX_ERROR);
				}
			}
			i = j;
		}
		else
			i++;
	}
	return (OK);
}

int	ft_start_pipe(t_vars *vars)
{
	int		i;
	char	*temp;

	temp = vars->inp;
	i = 0;
	while (temp[i] && (temp[i] == 32 || (temp[i] > 8 && temp[i] < 14)))
		i++;
	if (temp[i] == '|')
	{
		vars->exit_code = SYNTAX_ERROR;
		vars->no_exec = SYNTAX_ERROR;
		ft_printf_fd(2, "bash: syntax error near unexpected token `|'\n");
		return (SYNTAX_ERROR);
	}
	return (OK);
}

void	ft_check_input(t_vars *vars)
{
	if (ft_start_pipe(vars))
		return ;
	if (ft_check_redirect_file(vars))
		return ;
	ft_check_string_count(vars, vars->inp);
	ft_malloc_prog_2d_str(vars);
	ft_cleanup_lst(vars);
	ft_comb_progs(vars);
	ft_red_file(vars, vars->p_start);
	ft_cleanup_reds(vars);
	ft_expand_all_vars(vars);
	ft_pipecount(vars);
	ft_heredoc(vars);
}
