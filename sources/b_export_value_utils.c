/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_value_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:14:23 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/26 11:59:32 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_copy_value_exp(t_quote *quote, char *arg)
{
	int	i;

	i = 0;
	while (*arg)
	{
		if (*arg == '\'')
		{
			quote->value[i++] = '\\';
			quote->value[i++] = '\'';
		}
		else if (*arg == '"')
		{
			quote->value[i++] = '\\';
			quote->value[i++] = '"';
		}
		else
		{
			quote->value[i++] = *arg;
		}
		arg++;
	}
	quote->value[i] = '\0';
}

void	ft_quote_len_exp(t_quote *quote, char *arg)
{
	while (*arg)
	{
		if (*arg == '\'')
			quote->len += 2;
		else if (*arg == '"')
			quote->len += 2;
		else
			quote->len++;
		arg++;
	}
}

char	*ft_create_exp_value(t_vars *vars, char *arg)
{
	t_quote	quote;

	ft_init_quote(&quote);
	ft_quote_len_exp(&quote, arg);
	quote.value = (char *)ft_calloc((quote.len + 1), sizeof(char));
	if (!quote.value)
		ft_exit(vars, MALLOC_ERROR, 0);
	if (quote.len == 0)
		quote.value[0] = '\0';
	else
		ft_copy_value_exp(&quote, arg);
	return (quote.value);
}

char	*ft_exp_value(t_vars *vars, char *arg)
{
	char	*value;

	while (*arg != '=' && *arg != '\0')
		arg++;
	if (*arg == '\0')
		value = NULL;
	else
	{
		arg++;
		value = ft_create_exp_value(vars, arg);
	}
	return (value);
}
