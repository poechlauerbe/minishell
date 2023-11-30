/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:26:58 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 16:09:05 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

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

int	ft_remove_envv(t_vars *vars, char *key)
{
	t_keyval	*tmp;
	t_keyval	*tmp2;

	tmp = ft_val_retrieval(vars, key);
	if (!tmp)
		return (1);
	else
	{
		if (!tmp->prev && !tmp->next)
		{
			free (tmp);
			vars->envv = NULL;
		}
		else
		{
			if(!tmp->prev)
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
