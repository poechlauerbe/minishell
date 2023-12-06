/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:35:10 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 13:38:44 by tbenz            ###   ########.fr       */
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
