/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:32:28 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/17 13:15:10 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_varlen(char *arg, t_quote *quote)
{
	int	varlen;
	int	i;

	varlen = 1;
	i = quote->i + 1;
	if (ft_isdigit(arg[i]) || arg[i] == '?')
		return (2);
	if ((ft_isalpha(arg[i]) || arg[i] == '_'))
	{
		while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		{
			varlen++;
			i++;
		}
	}
	return (varlen);
}

void	ft_move_spaces(int *j, char *str, int *flag)
{
	while (str[*j] && (str[*j] == 32 || (str[*j] > 8 && str[*j] < 14)))
	{
		*flag = 1;
		*j += 1;
	}
}

int	ft_exp_remove_spaces(char *str, char *arg, int *i, int *j)
{
	int	flag;
	int	printed_signs;

	flag = 0;
	printed_signs = 0;
	while (str && str[*j])
	{
		ft_move_spaces(j, str, &flag);
		if (*i != 0 && flag)
		{
			arg[*i] = ' ';
			*i += 1;
			printed_signs++;
		}
		flag = 0;
		if (!str[*j])
			return (printed_signs);
		arg[*i] = str[*j];
		*i += 1;
		*j += 1;
		printed_signs++;
	}
	return (printed_signs);
}
