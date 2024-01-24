/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:55:29 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/24 16:07:30 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_enclosing_heredoc(char **arg, t_vars *vars)
{
	t_quote	quote;
	int		errcd;

	ft_init_quote(&quote);
	while (*arg && (*arg)[quote.i])
	{
		if (quote.i == 0)
			ft_init_quote(&quote);
		if ((*arg)[quote.i] == '\'' && !quote.dq && !quote.sq)
			quote.sq = 1;
		else if ((*arg)[quote.i] == '\'' && !quote.dq && quote.sq)
			quote.sq = 0;
		else if ((*arg)[quote.i] == '"' && !quote.sq && !quote.dq)
			quote.dq = 1;
		else if ((*arg)[quote.i] == '"' && !quote.sq && quote.dq)
			quote.dq = 0;
		quote.i++;
	}
	errcd = ft_enclosing_open_quotes(vars, quote);
	if (errcd)
	{
		vars->no_exec = SYNTAX_ERROR;
		vars->exit_code = SYNTAX_ERROR;
	}
	return (errcd);
}

void	ft_heredoc_append(t_vars *vars, t_prg *prog, char **str)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp = ft_strjoin(*str, "\n");
	if (!temp)
	{
		free(str);
		ft_exit(vars, MALLOC_ERROR);
	}
	if (*str)
		free(*str);
	*str = NULL;
	temp2 = ft_strjoin(prog->heredoc, temp);
	if (!temp2)
	{
		free(temp);
		ft_exit(vars, MALLOC_ERROR);
	}
	if (prog->heredoc)
		free(prog->heredoc);
	prog->heredoc = temp2;
	if (temp)
		free (temp);
}

void	ft_add_on_heredoc_str(t_vars *vars, t_prg *prog, char *str)
{
	if (prog->heredoc)
		ft_heredoc_append(vars, prog, &str);
	else
	{
		prog->heredoc = ft_strjoin(str, "\n");
		if (!prog->heredoc)
		{
			free(str);
			ft_exit(vars, MALLOC_ERROR);
		}
	}
	if (str)
		free (str);
	str = NULL;
}

void	ft_err_m_hered(t_prg *prog, int line_num)
{
	int	i;

	i = 0;
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(line_num, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	while (prog->prog[0][i + 1])
		i++;
	prog->prog[0][i] = '\0';
	ft_putstr_fd(prog->prog[0], 2);
	ft_putstr_fd("')\n", 2);
}
