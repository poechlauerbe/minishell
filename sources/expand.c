/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:15:16 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/16 11:07:47 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exp_remove_spaces(char *str, char *arg, int *i, int *j)
{
	int	flag;
	int	printed_signs;

	flag = 0;
	printed_signs = 0;
	while (str && str[*j])
	{
		while (str[*j] && (str[*j] == 32 || (str[*j] > 8 && str[*j] < 14)))
		{
			flag = 1;
			*j += 1;
		}
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

void	ft_expand_str(t_vars *vars, char **arg, t_quote *quote, char *str)
{
	int		strlen;
	int		varlen;
	char	*temp;
	int		printed_signs;
	int		i;
	int		j;

	temp = *arg;
	varlen = ft_varlen(*arg, quote);
	strlen = ft_strlen(*arg) - varlen + ft_strlen(str);
	*arg = ft_calloc((strlen + 1), sizeof(char));
	if (!arg)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	while (++i < quote->i)
		(*arg)[i] = temp[i];
	j = 0;
	printed_signs = ft_exp_remove_spaces(str, *arg, &i, &j);
	j = i - printed_signs + varlen;
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
		if (temp->prog[0])
			ft_check_resplit(vars, temp->prog[0], temp);
		if (temp->prog[1] && (temp->prog[1][0] == '-'))
			ft_check_addon_resplit(vars, temp->prog[1], temp);
		temp = temp->next;
	}
	temp = vars->p_start;
	while (temp)
	{
		printf("oper: %c$\n", temp->oper);
		i = -1;
		while (temp->prog[++i])
			printf("string[%i]: %s\n", i, temp->prog[i]);
		printf("\n");
		while(temp->out_file)
		{
			printf("out: %s, %c$\n", temp->out_file->file, temp->out_file->oper);
			temp->out_file = temp->out_file->next;
		}
		while(temp->in_file)
		{
			printf("in: %s, %c$\n", temp->in_file->file, temp->in_file->oper);
			temp->in_file = temp->in_file->next;
		}
		temp = temp->next;
	}
}
