/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:14:23 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/05 17:56:58 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init_quote(t_quote *quote)
{
	quote->dq = 0;
	quote->sq = 0;
	quote->len = 0;
	quote->i = 0;
}

void	ft_quote_len(t_quote *quote , char *arg)
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
		if ((*arg == '\'' && !quote->dq && !quote->sq) || (*arg == '\'' && \
			!quote->dq && quote->sq) || (*arg == '"' && quote->sq == 0 && \
			!quote->dq) || (arg[quote->i] == '"' && !quote->sq && quote->dq))
			continue ;
		else
			quote->len++;
	}
}

void	ft_create_value(t_quote *quote, char *arg)
{
	ft_init_quote(quote);
	ft_quote_len(quote, arg);
	quote->value = (char *)malloc(sizeof(char) * (quote->len + 1));
	if (!quote->value)
		return ((ft_putstr_fd("Error allocating memory", 2)));
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
		if ((*arg == '\'' && !quote->dq && !quote->sq) || (*arg == '\'' && \
			!quote->dq && quote->sq) || (*arg == '"' && quote->sq == 0 && \
			!quote->dq) || (arg[quote->i] == '"' && !quote->sq && quote->dq))
			arg++ ;
		else
			quote->value[quote->i++] = *arg;
	}
	quote->value[quote->i] = '\0';
}

char	*ft_check_quotess(char *arg)
{
	t_quote	quote;

	ft_init_quote(&quote);
	while (arg[quote.i])
	{
		if (arg[quote.i] == '\'' && !quote.dq && !quote.sq)
			quote.sq = 1;
		else if (arg[quote.i] == '\'' && !quote.dq && quote.sq)
			quote.sq = 0;
		else if (arg[quote.i] == '"' && !quote.sq && !quote.dq)
			quote.dq = 1;
		else if (arg[quote.i] == '"' && !quote.sq && quote.dq)
			quote.dq = 0;
		quote.i++;
	}
	if (quote.sq != 0 || quote.dq != 0)
		return (printf("It seems like you forgot to close your quotes"), NULL);
	ft_create_value(&quote, arg);
	return (quote.value);
}

char	*ft_exp_value(char *arg)
{
	char	*value;
	int		i;

	while (*arg != '=' && *arg != '\0')
		arg++;
	if (*arg == '\0')
	{
		value = (char *)malloc(sizeof(char));
		if (!value)
			return ((ft_putstr_fd("Error allocating memory", 2)), NULL);
		value[0] = '\0';
	}
	else
	{
		arg++;
		value = ft_check_quotess(arg);
	}
	return (value);
}

int	main(void)
{
	ft_printf("%s", ft_exp_value("abc=sdfsdaf"));
}
