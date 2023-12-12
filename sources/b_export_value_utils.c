/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_value_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:14:23 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/12 13:27:36 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_copy_value(t_quote *quote, char *arg)
{
	while (*arg)
	{
		if (*arg == '\'' && !quote->dq && !quote->sq)
			quote->sq = 1;
		else if (*arg == '\'' && !quote->dq && quote->sq)
			quote->sq = 0;
		else if (*arg == '"' && quote->sq == 0 && !quote->dq)
			quote->dq = 1;
		else if (*arg == '"' && !quote->sq && quote->dq)
			quote->dq = 0;
		if (((*arg == '\'' || *arg == '"') && !quote->dq && !quote->sq) \
			|| (*arg == '\'' && !quote->sq && quote->dq) || (*arg == '"' \
			&& quote->sq && !quote->dq))
			arg++;
		else
		{
			quote->value[quote->i++] = *arg;
			arg++;
		}
	}
	quote->value[quote->i] = '\0';
}

char	*ft_create_value(t_vars *vars, char *arg)
{
	t_quote	quote;

	ft_init_quote(&quote);
	ft_quote_len(&quote, arg);
	quote.value = (char *)malloc(sizeof(char) * (quote.len + 1));
	if (!quote.value)
		ft_exit(vars, MALLOC_ERROR);
	ft_copy_value(&quote, arg);
	return (quote.value);
}

char	*ft_exp_value(t_vars *vars, char *arg)
{
	char	*value;

	while (*arg != '=' && *arg != '\0')
		arg++;
	if (*arg == '\0')
	{
		value = (char *)malloc(sizeof(char));
		if (!value)
			ft_exit(vars, MALLOC_ERROR);
		value[0] = '\0';
	}
	else
	{
		arg++;
		if (ft_check_enclosing(&arg, vars))
			return (NULL);
		value = ft_create_value(vars, arg);
	}
	return (value);
}

void	ft_init_quote(t_quote *quote)
{
	quote->dq = 0;
	quote->sq = 0;
	quote->len = 0;
	quote->i = 0;
	quote->value = NULL;
}

void	ft_quote_len(t_quote *quote, char *arg)
{
	while (*arg)
	{
		if (*arg == '\'' && !quote->dq && !quote->sq)
			quote->sq = 1;
		else if (*arg == '\'' && !quote->dq && quote->sq)
			quote->sq = 0;
		else if (*arg == '"' && quote->sq == 0 && !quote->dq)
			quote->dq = 1;
		else if (arg[quote->i] == '"' && !quote->sq && quote->dq)
			quote->dq = 0;
		if (((*arg == '\'' || *arg == '"') && !quote->dq && !quote->sq) \
			|| (*arg == '\'' && quote->sq && !quote->dq) || (*arg == '"' \
			&& !quote->sq && quote->dq))
			arg++;
		else
		{
			quote->len++;
			arg++;
		}
	}
}
