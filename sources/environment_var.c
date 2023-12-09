/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:51:48 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/09 15:36:35 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* t_kv	*ft_alphabet_sort()
{

} */

t_kv	*ft_last_entry(t_kv *elem)
{
	while (elem->next)
		elem = elem->next;
	return (elem);
}

void	ft_create_env(t_vars *vars, char **envp)
{
	t_kv	*envv;
	t_kv	*last;

	while (*envp)
	{
		envv = (t_kv *)ft_calloc(1, sizeof(t_kv));
		if (!envv)
			return ; //exit, free memory
		envv->key = ft_exp_key(*envp);
		envv->val = ft_exp_value(*envp);
		envv->id = 'x';
		envv->next = NULL;
		if (!vars->envv)
		{
			envv->prev = NULL;
			vars->envv = envv;
		}
		else
		{
			last = ft_last_entry(vars->envv);
			last->next = envv;
			envv->prev = last;
		}
		envp++;
	}
}
