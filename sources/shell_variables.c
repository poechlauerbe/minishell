/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:51:31 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/22 13:05:30 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_shvar(t_vars *vars, t_prg *prog)
{
	char	*key;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(prog->prog[i])
	{
		if (strchr(prog->prog[i], '='))
		{
			key = ft_exp_key(vars, prog->prog[i], 1);
			val = ft_exp_value(vars, prog->prog[i]);
			if (!key || ! val)
			{
				if (key)
					free (key);
				if (val)
					free (val);
				return (1);
			}
			ft_add_envv(vars, key, val, 1);
			j++;
		}
		i++;
	}
	if (j)
		return (0);
	return (1);
}
