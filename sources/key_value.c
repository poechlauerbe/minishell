/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:26:58 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 17:18:34 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_keyval	*ft_val_retrieval(t_vars *vars, char *key)
{
	t_keyval	*tmp;

	if (!vars->envv)
		return (NULL);
	tmp = vars->envv;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		else
			tmp = tmp->next;
	}
	return (NULL);
}

void	ft_add_envv(t_vars *vars, char *key, char *val)
{
	t_keyval	*entry;
	t_keyval	*tmp;

	tmp = ft_val_retrieval(vars, key);
	if (tmp)
	{
		tmp->val = val;
		return ;
	}
	entry = (t_keyval *)malloc(sizeof(t_keyval));
	if (!entry)
		return ;
	entry->key = key;
	entry->val = val;
	entry->prev = NULL;
	if (!vars->envv)
		entry->next = NULL;
	else
	{
		entry->next = vars->envv;
		tmp = entry->next;
		tmp->prev = entry;
	}
	vars->envv = entry;
}

int	ft_remove_helper(t_vars *vars, t_keyval *tmp, char *key)
{
	t_keyval	*tmp2;

	if (!tmp->prev && !tmp->next)
	{
		free (tmp);
		vars->envv = NULL;
	}
	else
	{
		if (!tmp->prev)
			vars->envv = tmp->next;
		else
		{
			tmp2 = tmp->prev;
			tmp2->next = tmp->next;
		}
		free (tmp);
	}
	return (0);
}

int	ft_remove_envv(t_vars *vars, char *key)
{
	t_keyval	*tmp;
	t_keyval	*tmp2;

	tmp = ft_val_retrieval(vars, key);
	if (!tmp)
		return (1);
	else
		return (ft_remove_helper(vars, tmp, key));
}

char	*ft_return_val(t_vars *vars, char *key)
{
	t_keyval	*tmp;

	tmp = ft_val_retrieval(vars, key);
	if (!tmp)
		return (NULL);
	else
		return (tmp->val);
}
