/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_red_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:05:51 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/19 12:36:13 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_assing_reds(t_vars *vars, t_prg *tmp, t_prg **lst, t_prg *prog)
{
	tmp = *lst;
	while (tmp && tmp->oper != '|')
	{
		if (tmp->oper == '>' || tmp->oper == O_APP_OUT)
			ft_red_new_node(vars, &prog->out_file, tmp->prog[0], tmp->oper);
		else if (tmp->oper == '<' || tmp->oper == O_HEREDOC)
			ft_red_new_node(vars, &prog->in_file, tmp->prog[0], tmp->oper);
		tmp = tmp->next;
	}
	*lst = tmp;
}

void	ft_red_file(t_vars *vars, t_prg *lst)
{
	t_prg	*prog;
	t_prg	*tmp;

	tmp = lst;
	while (lst)
	{
		prog = NULL;
		if (tmp->oper == '|')
		{
			prog = tmp;
			tmp = tmp->next;
			lst = tmp;
		}
		while (tmp && tmp->oper != '|')
		{
			if (tmp->oper == '0' && prog == NULL)
				prog = tmp;
			tmp = tmp->next;
		}
		ft_assing_reds(vars, tmp, &lst, prog);
	}
}

void	ft_print_red_file_error(t_vars *vars, char *str, char c)
{
	ft_putstr_fd(M_SYN, 2);
	if (str)
		ft_putstr_fd(str, 2);
	if (c)
		ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	vars->no_exec = SYNTAX_ERROR;
	vars->exit_code = SYNTAX_ERROR;
}

void	ft_check_red_signs(t_vars *vars, t_prg *temp)
{
	if (!temp->prog[0] && !temp->next)
		ft_print_red_file_error(vars, "newline", '\0');
	else if (!temp->prog[0] && (temp->next->oper == '<'
			|| temp->next->oper == '>'))
		ft_print_red_file_error(vars, NULL, temp->next->oper);
	else if (!temp->prog[0] && (temp->next->oper == O_APP_OUT
			|| temp->next->oper == O_HEREDOC))
	{
		if (temp->next->oper == O_HEREDOC && !temp->next->prog[0]
			&& temp->next->next && (temp->next->next->oper == '<'
				|| temp->next->next->oper == O_HEREDOC))
			ft_print_red_file_error(vars, "<<<", '\0');
		else if (temp->next->oper == O_APP_OUT)
			ft_print_red_file_error(vars, ">>", '\0');
		else
			ft_print_red_file_error(vars, "<<", '\0');
	}
	else if (!temp->prog[0] && temp->next && temp->next->oper == '|')
		ft_print_red_file_error(vars, NULL, '|');
	// else if (temp->oper == O_HEREDOC && temp->prog[0])
	// 	ft_heredoc_exec(vars, temp);
}

int	ft_check_redirect_file(t_vars *vars)
{
	t_prg	*temp;

	temp = vars->p_start;
	while (temp)
	{
		if (temp->oper == '<' || temp->oper == '>' || temp->oper == O_APP_OUT
			|| temp->oper == O_HEREDOC)
		{
			ft_check_red_signs(vars, temp);
			if (vars->exit_code)
				return (vars->exit_code);
		}
		temp = temp->next;
	}
	return (OK);
}
