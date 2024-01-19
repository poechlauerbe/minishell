/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:41:53 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/19 16:55:51 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_export_prog(t_vars *vars, char **prog, int i)
{
	char	*key;
	char	*value;

	if (prog[i] && prog[i][0] == '-' && prog[i][1] != '\0')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_option_error(vars, prog[i]);
		return ;
	}
	while (prog[i])
	{
		key = ft_exp_key(vars, prog[i], 0);
		if (!key)
		{
			i++;
			continue ;
		}
		value = ft_exp_value(vars, prog[i]);
		ft_add_envv(vars, key, value, 0);
		ft_new_envp(vars);
		i++;
	}
}

void	ft_export(t_vars *vars)
{
	int		i;
	char	**prog;

	prog = vars->p_start->prog;
	i = 1;
	if (prog[i])
		ft_export_prog(vars, prog, i);
	else
		ft_export_print(vars);
}
