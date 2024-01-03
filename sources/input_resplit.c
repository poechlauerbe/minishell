/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_resplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:29:20 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/03 15:58:01 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strlen_resplit(char *str, int *i)
{
	int	str_len;

	str_len = 0;
	while (str[*i] && (str[*i] == 32 || (str[*i] > 8 && str[*i] < 14)))
		*i += 1;
	while (str[*i] && !(str[*i] == 32 || (str[*i] > 8 && str[*i] < 14)))
	{
		*i += 1;
		str_len++;
	}
	return (str_len);
}

void	ft_resplit(t_vars *vars, t_prg *prg, int count)
{
	int		c_progs;
	char	**new;
	char	*str_wo_q;
	int		i;
	int		str_len;

	str_wo_q = ft_create_value(vars, prg->prog[0]);
	if (!str_wo_q)
		ft_exit(vars, MALLOC_ERROR);
	free(prg->prog[0]);
	prg->prog[0] = str_wo_q;
	c_progs = 0;
	while (prg->prog[c_progs])
		c_progs++;
	new = ft_calloc((c_progs + count), sizeof(char *));
	if (!new)
		ft_exit(vars, MALLOC_ERROR);
	i = 0;
	c_progs = 0;
	while (str_wo_q[i])
	{
		str_len = ft_strlen_resplit(str_wo_q, &i);
		new[c_progs] = ft_calloc(str_len + 1, sizeof(char));
		if (!new[c_progs])
			ft_exit(vars, MALLOC_ERROR);
		ft_strlcpy(new[c_progs], &str_wo_q[i - str_len], str_len + 1);
		c_progs++;
	}
	i = 1;
	while (prg->prog[i])
	{
		new[c_progs] = prg->prog[i];
		c_progs++;
		i++;
	}
	free(prg->prog);
	prg->prog = new;
}

void	ft_check_resplit(t_vars *vars, char *str, t_prg *prg)
{
	int	count;
	int	i;
	int	assign_f;

	count = 1;
	i = 0;
	assign_f = 0;

	while (str[i] && (str[i] == 32 || (str[i] > 8 && str[i] < 14)))
		i++;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	if (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		count++;
	i++;
	if (count > 1)
	{
		while (str[i] && !assign_f)
		{
			while (str[i] && (str[i] == 32 || (str[i] > 8 && str[i] < 14)))
				i++;
			while (str[i] && ft_isalpha(str[i]))
				i++;
			if (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
				count++;
			i++;
		}
		ft_printf("check: %i\n", count);
		ft_resplit(vars, prg, count);
	}
}
