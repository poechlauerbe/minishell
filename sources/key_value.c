/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:26:58 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/18 11:13:25 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_new_value(t_vars *vars, char *key, char *val)
{
	int		len;
	t_kv	*tmp;

	tmp = vars->envv;
	while (tmp)
	{
		if (!strcmp(tmp->key, key))
			break ;
		tmp = tmp->next;
	}
	if (tmp->val)
	{
		len = ft_strlen(val);
		free (tmp->val);
		tmp->val = (char *)calloc((len + 1), sizeof(char));
		ft_strlcpy(tmp->val, val, (len + 1));
	}
}

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
		if (val[0])
			ft_new_value(vars, key, val);
		return ;
	}
	tmp = (t_kv *)malloc(sizeof(t_kv));
	if (!tmp)
		ft_exit(vars, MALLOC_ERROR);
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
