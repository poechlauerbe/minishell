/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_resplit_addon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:52:41 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_resplit_addon2(t_vars *vars, char *str, t_prg *prg, char **new)
{
	int		i;
	int		str_len;

	i = 0;
	str_len = ft_strlen_resplit(str, &i);
	new[1] = ft_calloc(str_len + 1, sizeof(char));
	if (!new[1])
		ft_exit(vars, MALLOC_ERROR, 0);
	ft_strlcpy(new[1], &str[i - str_len], str_len + 1);
	while (str[i] && (str[i] == 32 || (str[i] > 8 && str[i] < 14)))
		i += 1;
	str_len = ft_strlen(&str[i]);
	new[2] = ft_calloc(str_len + 1, sizeof(char));
	if (!new[2])
		ft_exit(vars, MALLOC_ERROR, 0);
	ft_strlcpy(new[2], &str[i], str_len + 1);
	i = 2;
	while (prg->prog[i])
	{
		new[i + 1] = prg->prog[i];
		i++;
	}
	free(prg->prog);
	prg->prog = new;
}

void	ft_resplit_addon(t_vars *vars, t_prg *prg, int count)
{
	int		c_progs;
	char	**new;
	char	*str_wo_q;

	str_wo_q = ft_create_value(vars, prg->prog[1]);
	if (!str_wo_q)
		ft_exit(vars, MALLOC_ERROR, 0);
	free(prg->prog[1]);
	prg->prog[1] = str_wo_q;
	c_progs = 0;
	while (prg->prog[c_progs])
		c_progs++;
	new = ft_calloc((c_progs + count), sizeof(char *));
	if (!new)
		ft_exit(vars, MALLOC_ERROR, 0);
	new[0] = prg->prog[0];
	ft_resplit_addon2(vars, prg->prog[1], prg, new);
}

void	ft_check_addon_resplit(t_vars *vars, char *str, t_prg *prg)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] > 8 && str[i] < 14)))
		i++;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '-'))
		i++;
	if (str[i] == ' ' || (str[i] > 8 && str[i++] < 14))
		count++;
	if (count > 1)
		ft_resplit_addon(vars, prg, count);
}
