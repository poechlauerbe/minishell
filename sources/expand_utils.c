/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:32:28 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/09 10:32:48 by bpochlau         ###   ########.fr       */
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
		while (arg[i] && ft_isalnum(arg[i]))
		{
			varlen++;
			i++;
		}
	}
	return (varlen);
}
