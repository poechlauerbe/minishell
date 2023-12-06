/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:35:10 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 16:45:39 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_vars *vars)
{
	int			i;
	t_keyval	*tmp;

	if (!vars->envp || !vars->envp[0])
		ft_printf("\n");
	i = 0;
	while (vars->envp[i])
	{
		ft_printf("%s\n", vars->envp[i]);
		i++;
	}
	i = 0;
	tmp = vars->envv;
	if (tmp)
	{
		while (tmp)
		{
			ft_printf("%s=%s", tmp->key, tmp->val);
			tmp = tmp->next;
		}
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
			id = ft_exp_key(vars->p_start->prog[i]);
			if (!id)
				return ;
			value = ft_exp_value(vars->p_start->prog[i]);
			if (!value)
				return ;
			ft_printf("%s=%s\n", id, value); //has to be removed when functioning well
			ft_add_envv(vars, id, value); //has to add to envv
			free (id);
			free(value);
			i++;
		}
	}
	else
		ft_env(vars);
}
