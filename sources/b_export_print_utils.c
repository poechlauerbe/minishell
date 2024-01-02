/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_print_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:36:23 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/02 19:04:33 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_ao(t_vars *vars, t_kv *elem)
{
	t_kv	*prev;

	prev = ft_first_kv(vars->envv);
	if (!prev)
		return ;
	if (ft_strcmp(elem->key, prev->key) < 0)
		ft_set_ptr(vars, &elem, NULL);
	else
	{
		while (prev && prev->nxtao)
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

void	ft_key_err_print(t_vars *vars, char *key, char *val)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: export: `", key);
	if (!tmp1)
		ft_exit(vars, MALLOC_ERROR);
	tmp2 = ft_strjoin(tmp1, val);
	free(tmp1);
	if (!tmp2)
		ft_exit(vars, MALLOC_ERROR);
	tmp1 = ft_strjoin(tmp2, "': not a valid identifier\n");
	free(tmp2);
	if (!tmp1)
		ft_exit(vars, MALLOC_ERROR);
	ft_printf_fd(2, tmp1);
	free (tmp1);
	vars->exit_code = 1;
}
