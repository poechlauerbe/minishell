/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:15:16 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/12 13:59:38 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_varlen(char *arg, t_quote *quote)
{
	int	varlen;
	int	i;

	varlen = 1;
	i = quote->i + 1;
	if (ft_isdigit(arg[i]))
	{
		return (2)
	}
	return (varlen);
}

void	ft_expand_str(t_vars *vars, char **arg, t_quote *quote, char *str)
{
	int	strlen;
	int varlen;

	varlen = ft_varlen(*arg, quote);
	strlen = quote->len - varlen + ft_strlen(str);
}

void	ft_dig_expand(t_vars *vars, char **arg, t_quote *quote, int i)
{
	char	*temp;

	temp = *arg;
	if (temp[i] == '0')
		ft_expand_str(vars, arg, quote, "minishell");
	else
		ft_expand_str(vars, arg, quote, "");
	free(temp);
}

void	ft_expander(t_vars *vars, char **arg, t_quote *quote)
{
	int		i;
	char	*str;

	i = quote->i + 1;
	str = *arg;
	if (ft_isdigit(str[i]) == 1)
		ft_dig_expand(vars, arg, quote, i);

}

int	ft_check_exit_code(t_vars *vars)
{
	return (vars->exit_code);
}
