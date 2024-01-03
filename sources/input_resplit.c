/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_resplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:29:20 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/03 14:36:48 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_resplit(t_vars *vars, t_prg *prg, int count)
{
	int		c_progs;
	char	**new;
	char	*str_wo_q;

	c_progs = 0;
	while (prg->prog[c_progs])
		c_progs++;
	new = ft_calloc((c_progs + count), sizeof(char *));
	if (!new)
		ft_exit(vars, MALLOC_ERROR);
	str_wo_q = ft_create_value(vars, prg->prog[0]);
	if (!str_wo_q)
		ft_exit(vars, MALLOC_ERROR);
	free(prg->prog[0]);
	prg->prog[0] = str_wo_q;
}

void	ft_check_resplit(t_vars *vars, char *str, t_prg *prg)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == 32 || (str[i] > 8 && str[i] < 14)))
			i++;
		while (ft_isalpha(str[i]) || str[i] == '\"')
			i++;
		if (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
			count++;
		i++;
	}
	if (count > 1)
		ft_resplit(vars, prg, count);
}
