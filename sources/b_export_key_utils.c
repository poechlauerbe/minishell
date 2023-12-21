/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_key_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:22:09 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/21 15:03:40 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_enclosing(char **arg, t_vars *vars)
{
	t_quote	quote;

	ft_init_quote(&quote);
	while ((*arg)[quote.i])
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
		if (quote.sq != 1 && (*arg)[quote.i] == '$')
			ft_expander(vars, arg, &quote);
		quote.i++;
	}
	if (quote.sq != 0 || quote.dq != 0)
	{
		ft_putstr_fd("It seems like you forgot to close your quotes\n", 2);
		return (1);
	}
	return (0);
}

char	*ft_copy_key(t_vars *vars, char *arg)
{
	int		i;
	char	*id;

	id = (char *)malloc(sizeof(char) * (ft_key_len(arg) + 1));
	if (!id)
		ft_exit(vars, MALLOC_ERROR);
	i = 0;
	while (*arg && *arg != '=')
	{
		if (*arg != '\'' && *arg != '"')
		{
			id[i] = *arg;
			i++;
		}
		arg++;
	}
	id[i] = '\0';
	return (id);
}

char	*ft_exp_key(t_vars *vars, char *arg)
{
	char	*id;
	char	*comp;

	comp = arg;
	while (*comp && (*comp != '=' && *comp != '\0'))
		comp++;
	if (*arg == '"' || *arg == '\'')
	{
		if (ft_check_enclosing(&arg, vars))
			return (NULL);
		arg++;
	}
	id = ft_copy_key(vars, arg);
	if (!id)
		return (NULL);
	if (!ft_exp_keychecker(id, comp))
		return (id);
	else
	{
		free(id);
		return (NULL);
	}
}

int	ft_exp_keychecker(char *arg, char *comp)
{
	int	j;

	j = 0;
	if (arg[j] == '\'' || arg[j] == '"')
		j++;
	if (ft_isalpha(arg[j]) || arg[j] == '_')
		j++;
	else
	{
		ft_printf_fd(2, "export: not an identifier: `%s%s'\n", arg, comp);
		return (1);
	}
	while (ft_isalnum(arg[j]) || arg[j] == '_')
		j++;
	if (arg[j] == '\'' || arg[j] == '"')
		j++;
	if ((arg[j] != '=' && arg[j] != '\0'))
	{
		ft_printf_fd(2, "export: not an identifier: `%s%s'\n", arg, comp);
		return (1);
	}
	return (0);
}

int	ft_key_len(char *arg)
{
	int	len;

	len = 0;
	while (*arg && *arg != '=')
	{
		if (*arg != '"' && *arg != '\'')
			len++;
		arg++;
	}
	return (len);
}
