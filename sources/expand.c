/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:15:16 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_expand_str(t_vars *vars, char **arg, t_quote *quote, char *str)
{
	int		strlen;
	int		varlen;
	char	*temp;
	int		printed_signs;
	t_count	num;

	temp = *arg;
	varlen = ft_varlen(*arg, quote);
	strlen = ft_strlen(*arg) - varlen + ft_strlen(str);
	*arg = ft_calloc((strlen + 1), sizeof(char));
	if (!(*arg))
		ft_exit(vars, MALLOC_ERROR, 0);
	num.i = -1;
	while (++num.i < quote->i)
		(*arg)[num.i] = temp[num.i];
	num.j = 0;
	printed_signs = ft_exp_remove_spaces(str, *arg, &num.i, &num.j);
	num.j = num.i - printed_signs + varlen;
	while (temp[num.j])
		(*arg)[num.i++] = temp[num.j++];
	(*arg)[num.i] = '\0';
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
		ft_exit(vars, MALLOC_ERROR, 0);
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
			ft_exit(vars, MALLOC_ERROR, 0);
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
	t_prg	*tmp;
	int		i;

	tmp = vars->p_start;
	while (tmp)
	{
		i = 0;
		while (tmp->prog[i])
		{
			ft_home_expand(vars, &tmp->prog[i]);
			ft_check_enclosing(&tmp->prog[i], vars);
			i++;
		}
		if (tmp->prog[0])
			ft_check_resplit(vars, tmp->prog[0], tmp);
		if (tmp->prog[1] && (tmp->prog[1][0] == '-'))
			ft_check_addon_resplit(vars, tmp->prog[1], tmp);
		tmp = tmp->next;
	}
}
