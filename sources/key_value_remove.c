/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:55:38 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/22 12:17:13 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_remove_envv(t_vars *vars, char *key)
{
	t_kv	*tmp;

	tmp = ft_val_retrieval(vars, key);
	if (!tmp)
		return (1);
	else
		return (ft_remove_helper(vars, tmp));
}

int	ft_remove_helper(t_vars *vars, t_kv *tmp)
{
	ft_remove_links_ao(&tmp);
	free(tmp->key);
	free(tmp->val);
	if (!tmp->prev && !tmp->next)
	{
		free (tmp);
		vars->envv = NULL;
	}
	else
	{
		ft_remove_links(&tmp, &vars->envv);
		free (tmp);
	}
	return (0);
}

void	ft_remove_links(t_kv **tmp, t_kv **envv)
{
	t_kv	*tmp2;

	if (!(*tmp)->prev)
	{
		*envv = (*tmp)->next;
		(*envv)->prev = NULL;
	}
	else
	{
		if ((*tmp)->prev)
		{
			tmp2 = (*tmp)->prev;
			tmp2->next = (*tmp)->next;
		}
		if ((*tmp)->next)
		{
			tmp2 = (*tmp)->next;
			tmp2->prev = (*tmp)->prev;
		}
	}
}

void	ft_remove_links_ao(t_kv **tmp)
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
