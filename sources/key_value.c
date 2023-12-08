/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:26:58 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/08 17:53:19 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_kv	*ft_val_retrieval(t_vars *vars, char *key, int i)
{
	t_kv	*tmp;
	t_kv	*var;

	if (!i)
		var = vars->envv;
	else
		var = vars->shvar;
	if (!var)
		return (NULL);
	tmp = var;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		else
			tmp = tmp->next;
	}
	return (NULL);
}

void	ft_add_envv(t_vars *vars, char *key, char *val, int i)
{
	t_kv	*tmp;

	tmp = ft_val_retrieval(vars, key, i);
	if (tmp)
	{
		tmp->val = val;
		return ;
	}
	tmp = (t_kv *)malloc(sizeof(t_kv));
	if (!tmp)
		return ;
	if (!i)
		ft_set_val(vars, &vars->envv, &tmp, key, val);
	else
		ft_set_val(vars, &vars->shvar, &tmp, key, val);
}

int	ft_remove_helper(t_vars *vars, t_kv *tmp, int i)
{
	t_kv	*tmp2;
	t_kv	**var;

	if (!i)
		var = &vars->envv;
	else
		var = &vars->shvar;
	if (!tmp->prev && !tmp->next)
	{
		free (tmp);
		*var = NULL;
	}
	else
	{
		if (!tmp->prev)
			*var = tmp->next;
		else
		{
			tmp2 = tmp->prev;
			tmp2->next = tmp->next;
		}
		free (tmp);
	}
	return (0);
}

int	ft_remove_envv(t_vars *vars, char *key, int i)
{
	t_kv	*tmp;

	tmp = ft_val_retrieval(vars, key, i);
	if (!tmp)
		return (1);
	else
		return (ft_remove_helper(vars, tmp, i));
}

char	*ft_return_val(t_vars *vars, char *key, int i)
{
	t_kv	*tmp;

	tmp = ft_val_retrieval(vars, key, i);
	if (!tmp)
		return (NULL);
	else
		return (tmp->val);
}
