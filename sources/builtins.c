/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:49:29 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/11 14:11:47 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// something is not working well here
void	ft_env(t_vars *vars)
{
	int		i;
	t_kv	*tmp;

	if (!vars->envv)
		ft_printf("\n");
	i = 0;
	tmp = vars->envv;
	while (tmp)
	{
		if (tmp->id == 'x')
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

void	ft_export(t_vars *vars)
{
	int		i;
	char	*id;
	char	*value;

	i = 1;
	if (vars->p_start->prog[i])
	{
		while (vars->p_start->prog[i])
		{
			id = ft_exp_key(vars, vars->p_start->prog[i]);
			if (!id)
				return ;
			value = ft_exp_value(vars, vars->p_start->prog[i]);
			if (!value)
				return ;
			ft_add_envv(vars, id, value, 0);
			i++;
		}
	}
	else
		ft_export_print(vars);
}

void	ft_unset(t_vars *vars)
{
	char	*key;
	int		i;

	i = 1;
	key = vars->p_start->prog[i];
	while (key)
	{
		ft_remove_envv(vars, key);
		key = vars->p_start->prog[++i];
	}
}
