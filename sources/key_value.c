/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:26:58 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/09 13:43:20 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_kv	*ft_val_retrieval(t_vars *vars, char *key)
{
	t_kv	*tmp;
	t_kv	*var;

	var = vars->envv;
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

void	ft_add_envv(t_vars *vars, char *key, char *val, int id)
{
	t_kv	*tmp;

	tmp = ft_val_retrieval(vars, key);
	if (tmp)
	{
		if (!id)
			tmp->id = 'x';
		if (!tmp->val[0] && val[0])
			tmp->val = val;
		return ;
	}
	tmp = (t_kv *)malloc(sizeof(t_kv));
	if (!tmp)
		return ;
	ft_set_val(vars, &vars->envv, &tmp, key, val);
	if (!id)
		tmp->id = 'x';
	else
		tmp->id = 's';
}

void	ft_remove_link_adj(t_kv **tmp)
{
	t_kv	*tmp2;

	if ((*tmp)->prvao)
	{
		tmp2 = (*tmp)->prvao;
		tmp2->nxtao = (*tmp)->nxtao;
	}
	if ((*tmp)->nxtao)
	{
		tmp2 = (*tmp)->nxtao;
		tmp2->prvao = (*tmp)->prvao;
	}
}

int	ft_remove_helper(t_vars *vars, t_kv *tmp)
{
	t_kv	**var;
	t_kv	*tmp2;

	var = &vars->envv;
	ft_remove_link_adj(&tmp);
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
			if (tmp->prev)
			{
				tmp2 = tmp->prev;
				tmp2->next = tmp->next;
			}
			if (tmp->next)
			{
				tmp2 = tmp->next;
				tmp2->prev = tmp->prev;
			}
		}
		free (tmp);
	}
	return (0);
}

int	ft_remove_envv(t_vars *vars, char *key)
{
	t_kv	*tmp;

	tmp = ft_val_retrieval(vars, key);
	if (!tmp)
		return (1);
	else
		return (ft_remove_helper(vars, tmp));
}

char	*ft_return_val(t_vars *vars, char *key)
{
	t_kv	*tmp;

	tmp = ft_val_retrieval(vars, key);
	if (!tmp)
		return (NULL);
	else
		return (tmp->val);
}
