/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:26:58 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/09 15:21:09 by tbenz            ###   ########.fr       */
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
	tmp->key = key;
	tmp->val = val;
	ft_set_val(vars, &vars->envv, &tmp);
	if (!id)
		tmp->id = 'x';
	else
		tmp->id = 's';
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
