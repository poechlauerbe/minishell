/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_key_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:22:09 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_enclosing(char **arg, t_vars *vars)
{
	t_quote	quote;

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
		if (quote.sq != 1 && (*arg)[quote.i] == '$')
			ft_expander(vars, arg, &quote);
		quote.i++;
	}
	return (ft_enclosing_open_quotes(vars, quote));
}

char	*ft_copy_key(t_vars *vars, char *arg)
{
	int		i;
	char	*id;

	id = (char *)malloc(sizeof(char) * (ft_key_len(arg) + 1));
	if (!id)
		ft_exit(vars, MALLOC_ERROR, 0);
	i = 0;
	while (*arg && !(*arg == '=' || (*arg == '+' && *(arg + 1) == '=')))
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

char	*ft_exp_key(t_vars *vars, char *arg, int func)
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
	if (!ft_exp_keychecker(vars, id, comp, func))
		return (id);
	else
	{
		vars->exit_code = 1;
		free(id);
		return (NULL);
	}
}

int	ft_exp_keychecker(t_vars *vars, char *arg, char *comp, int func)
{
	int	j;

	j = 0;
	if (arg[j] == '\'' || arg[j] == '"')
		j++;
	if (ft_isalpha(arg[j]) || arg[j] == '_')
		j++;
	else
	{
		if (!func)
			ft_key_err_print(vars, arg, comp);
		return (1);
	}
	while (ft_isalnum(arg[j]) || arg[j] == '_')
		j++;
	if (arg[j] == '\'' || arg[j] == '"')
		j++;
	if (arg[j] && !(arg[j] == '=' || (arg[j] == '+' && arg[j + 1] == '=')))
	{
		if (!func)
			ft_key_err_print(vars, arg, comp);
		return (1);
	}
	return (0);
}

int	ft_key_len(char *arg)
{
	int	len;

	len = 0;
	while (*arg && !(*arg == '=' || (*arg == '+' && *(arg + 1) == '=')))
	{
		if (*arg != '"' && *arg != '\'')
			len++;
		arg++;
	}
	return (len);
}
