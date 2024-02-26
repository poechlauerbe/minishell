/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:02:10 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/26 14:16:33 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_kv	*ft_first_kv(t_kv *elem)
{
	t_kv	*first;

	first = elem;
	while (elem)
	{
		if (ft_strcmp(first->key, elem->key) > 0)
			first = elem;
		elem = elem->next;
	}
	return (first);
}

t_kv	*ft_last_kv(t_kv *elem)
{
	t_kv	*last;

	last = elem;
	while (elem)
	{
		if (ft_strcmp(last->key, elem->key) < 0)
			last = elem;
		elem = elem->next;
	}
	return (last);
}

t_kv	*ft_next_kv(t_kv *elem, t_kv *prev, t_kv *last)
{
	t_kv	*next;

	next = last;
	while (elem)
	{
		if ((ft_strcmp(prev->key, elem->key) < 0)
			&& (ft_strcmp(elem->key, next->key) < 0))
			next = elem;
		elem = elem->next;
	}
	if (ft_strcmp(prev->key, next->key) > 1)
		return (NULL);
	return (next);
}

void	ft_order_envv(t_vars *vars)
{
	t_kv	*first;
	t_kv	*next;
	t_kv	*prev;
	t_kv	*last;

	first = ft_first_kv(vars->envv);
	last = ft_last_kv(vars->envv);
	next = ft_next_kv(vars->envv, first, last);
	first->nxtao = next;
	first->prvao = NULL;
	next->prvao = first->nxtao;
	while (next)
	{
		prev = next;
		next = ft_next_kv(vars->envv, next, last);
		prev->nxtao = next;
		next->prvao = prev;
		if (next == last)
			return ;
	}
}

void	ft_export_print(t_vars *vars)
{
	t_kv	*first;

	first = ft_first_kv(vars->envv);
	while (first)
	{
		if (first->id == 'x' && ft_strcmp(first->key, "_"))
		{
			if (first->val)
				ft_printf("declare -x %s=\"%s\"\n", first->key, first->val);
			else
				ft_printf("declare -x %s\n", first->key);
		}
		first = first->nxtao;
	}
}
