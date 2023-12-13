/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:15:16 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/12 17:36:43 by bpochlau         ###   ########.fr       */
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
	strlen = ft_strlen(*arg)- varlen + ft_strlen(str);
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
		;
	
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
			ft_check_enclosing(&temp->prog[i], vars);
			i++;
		}
		temp = temp->next;
	}
}

int	ft_check_exit_code(t_vars *vars)
{
	return (vars->exit_code);
}
