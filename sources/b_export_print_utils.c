/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_print_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:36:23 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/09 14:37:00 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_ao(t_vars *vars, t_kv *elem)
{
	t_kv	*prev;

	prev = ft_first_kv(vars->envv);
	if (ft_strcmp(elem->key, prev->key) < 0)
		ft_set_ptr(vars, &elem, NULL);
	else
	{
		while (prev->nxtao)
		{
			if (ft_strcmp(elem->key, prev->key) < 0)
			{
				ft_set_ptr(vars, &elem, prev->prvao);
				return ;
			}
			prev = prev->nxtao;
		}
		ft_set_ptr(vars, &elem, prev);
	}
}

void	ft_set_ptr(t_vars *vars, t_kv **elem, t_kv *prev)
{
	t_kv	*next;

	if (prev)
	{
		(*elem)->prvao = prev;
		(*elem)->nxtao = prev->nxtao;
		prev->nxtao = (*elem);
		next = (*elem)->nxtao;
		if (next)
			next->prvao = (*elem);
	}
	else
	{
		(*elem)->prvao = NULL;
		next = ft_first_kv(vars->envv);
		(*elem)->nxtao = next;
		next->prev = (*elem);
	}
}
