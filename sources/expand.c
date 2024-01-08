/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:15:16 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/08 18:44:01 by thorben          ###   ########.fr       */
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

void	ft_expand_str(t_vars *vars, char **arg, t_quote *quote, char *str)
{
	int		strlen;
	int		varlen;
	char	*temp;
	int		i;
	int		j;

	temp = *arg;
	varlen = ft_varlen(*arg, quote);
	strlen = ft_strlen(*arg) - varlen + ft_strlen(str);
	*arg = malloc((strlen + 1) * sizeof(char));
	if (!arg)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	while (++i < quote->i)
		(*arg)[i] = temp[i];
	j = 0;
	while (str && str[j])
		(*arg)[i++] = str[j++];
	j = i - j + varlen;
	while (temp[j])
		(*arg)[i++] = temp[j++];
	(*arg)[i] = '\0';
	if (temp)
		free(temp);
}

void	ft_dig_expand(t_vars *vars, char **arg, t_quote *quote, int i)
{
	char	*temp;

	temp = *arg;
	if (temp[i] == '0')
		ft_expand_str(vars, arg, quote, "minishell");
	else
		ft_expand_str(vars, arg, quote, "");
}

void	ft_expand_env(t_vars *vars, char **arg, t_quote *quote, int i)
{
	char	*temp;
	char	*str;
	int		len;

	len = ft_varlen(*arg, quote);
	str = malloc(len * sizeof(char));
	if (!str)
		ft_exit(vars, MALLOC_ERROR);
	ft_strlcpy(str, &(arg[0][i]), len);
	temp = ft_return_val(vars, str);
	free (str);
	if (temp)
	{
		ft_expand_str(vars, arg, quote, temp);
	}
	else if (len == 1)
		ft_expand_str(vars, arg, quote, "$");
	else
	{
		ft_expand_str(vars, arg, quote, "");
		quote->i--;
	}
}

void	ft_expander(t_vars *vars, char **arg, t_quote *quote)
{
	int		i;
	char	*str;
	char	*temp;

	i = quote->i + 1;
	str = *arg;
	if (ft_isdigit(str[i]) == 1)
		ft_dig_expand(vars, arg, quote, i);
	else if (str[i] == '?')
	{
		temp = ft_itoa(vars->exit_code);
		if (!temp)
			ft_exit(vars, MALLOC_ERROR);
		ft_expand_str(vars, arg, quote, temp);
		free(temp);
	}
	else if (str[i] == ' ')
		str[i] = ' ';
	else if (str[i] == '\"' && quote->dq == 0)
		ft_expand_str(vars, arg, quote, "\"");
	else if (str[i] == '\'')
		ft_expand_str(vars, arg, quote, "\'");
	else if (ft_isalpha(str[i]) || str[i] == '_')
		ft_expand_env(vars, arg, quote, i);
}

void	ft_expand_all_vars(t_vars *vars)
{
	t_prg	*temp;
	int		i;

	temp = vars->p_start;
	while (temp)
	{
		i = 0;
		while (temp->prog[i])
		{
			ft_home_expand(vars, &temp->prog[i]);
			ft_check_enclosing(&temp->prog[i], vars);
			i++;
		}
		// ft_check_resplit(vars, temp->prog[0], temp);
		temp = temp->next;
	}
}
