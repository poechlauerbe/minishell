/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_new_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:41:51 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/20 17:48:52 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_envp_len(t_vars *vars)
{
	int		len;
	t_kv *tmp;

	len = 0;
	tmp = vars->envv;
	while (tmp)
	{
		if (tmp->id == 'x')
			len++;
		tmp = tmp->next;
	}
	return (len);
}

void	ft_malloc_envp(t_vars *vars, char ***arr)
{
	int		i;
	int		idl;
	int		vall;
	char	*tmp;
	t_kv	*tmp2;

	i = 0;
	tmp2 = vars->envv;
	while (tmp2)
	{
		if (tmp2->id == 'x')
		{
			idl = ft_strlen(tmp2->key);
			if (tmp2->val)
				vall = ft_strlen(tmp2->val);
			tmp = ft_calloc(idl+ vall + 2, sizeof(char));
			if (!tmp)
				ft_exit(vars, MALLOC_ERROR);
			ft_strlcpy(tmp, tmp2->key, idl + 1);
			ft_strlcat(tmp, "=", idl + 2);
			if (tmp2->val)
			ft_strlcat(tmp, tmp2->val, idl + vall + 2);
			(*arr)[i] = tmp;
			i++;
		}
		tmp2 = tmp2->next;
	}
}

void	ft_free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free (envp[i]);
		i++;
	}
	free (envp);
}

void	ft_new_envp(t_vars *vars)
{
	int 	len;
	char	**arr;

	len = ft_envp_len(vars);
	arr = ft_calloc(len + 1, sizeof(char *));
	if (!arr)
		ft_exit(vars, MALLOC_ERROR);
	ft_malloc_envp(vars, &arr);
	if (vars->alloc)
		ft_free_envp(vars->envp);
	vars->envp = arr;
	if (!vars->alloc)
		vars->alloc = 1;
}

void	ft_malloc_envpr(t_vars *vars, char ***arr, char *key)
{
	int		j;
	int		len;
	char	*tmp;
	t_kv	*tmp2;

	j = 0;
	tmp2 = vars->envv;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->key, key))
			;
		else
		{
			len = ft_strlen(tmp2->key) + ft_strlen(tmp2->key) + 2;
			tmp = ft_calloc(len, sizeof(char));
			ft_strlcpy(tmp, tmp2->key, ft_strlen(tmp2->key) + 1);
			ft_strlcat(tmp, "=", ft_strlen(tmp2->key) + 2);
			ft_strlcat(tmp, tmp2->val, len);
			(*arr)[j++] = tmp;
		}
		tmp2 = tmp2->next;
	}
}

void	ft_remove_envp(t_vars *vars, char *key)
{
	int		len;
	char	**arr;

	len = ft_envp_len(vars);
	arr = ft_calloc(len, sizeof(char *));
	if (!arr)
		ft_exit(vars, MALLOC_ERROR);
	ft_malloc_envpr(vars, &arr, key);
	if (vars->alloc)
		ft_free_envp(vars->envp);
	vars->envp = arr;
	if (!vars->alloc)
		vars->alloc = 1;
}