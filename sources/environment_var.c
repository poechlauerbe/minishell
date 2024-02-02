/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:51:48 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_underscore_envv(t_vars *vars, char *prg)
{
	char	*key;
	char	*val;

	key = ft_strdup("_");
	val = ft_strdup(prg);
	if (!key || !val)
	{
		if (key)
			free (key);
		if (val)
			free (val);
		ft_exit(vars, MALLOC_ERROR, 0);
	}
	ft_add_envv(vars, key, val, 0);
	ft_new_envp(vars);
}

void	ft_add_underscore(t_vars *vars, char **prg)
{
	int		i;

	i = 0;
	while (prg && prg[i])
	{
		if (prg[i + 1])
			i++;
		else
		{
			ft_create_underscore_envv(vars, prg[i]);
			break ;
		}
	}
}

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
			ft_exit(vars, MALLOC_ERROR, 0);
		envv->key = ft_exp_key(vars, *envp, 0);
		envv->val = ft_exp_value(vars, *envp);
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
