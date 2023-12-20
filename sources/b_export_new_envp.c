/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_new_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:41:51 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/20 13:40:35 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_envp_len(t_vars *vars)
{
	int		len;
	char **tmp;

	len = 0;
	tmp = vars->envp;
	while (*tmp)
	{
		tmp++;
		len++;
	}
	return (len);
}

void	ft_malloc_envp(t_vars *vars, char ***arr, char **str)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (vars->envp[i])
	{
		len = ft_strlen(vars->envp[i]);
		tmp = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(tmp, vars->envp[i], len + 1);
		(*arr)[i] = tmp;
		i++;
	}
	(*arr)[i] = *str;
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

void	ft_new_envp(t_vars *vars, char *id, char *val)
{
	int 	len;
	char	**arr;
	char	*str;

	len = ft_envp_len(vars);
	arr = ft_calloc(len + 2, sizeof(char *));
	str = ft_calloc (ft_strlen(id) + ft_strlen(val) + 2, sizeof(char));
	if (!arr || !str)
		ft_exit(vars, MALLOC_ERROR);
	ft_strlcat(str, id, ft_strlen(id) + 1);
	ft_strlcat(str, "=", ft_strlen(str) + 2);
	ft_strlcat(str, val, ft_strlen(str) + ft_strlen(val) + 1);
	ft_malloc_envp(vars, &arr, &str);
	if (vars->alloc)
		ft_free_envp(vars->envp);
	vars->envp = arr;
	if (!vars->alloc)
		vars->alloc = 1;
}

void	ft_malloc_envpr(t_vars *vars, char ***arr, char *id)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	while (vars->envp[i])
	{
		len = ft_strlen(id);
		if (!ft_strncmp(vars->envp[i], id, len) && vars->envp[i][len] == '=')
			;
		else
		{
			len = ft_strlen(vars->envp[i]);
			tmp = ft_calloc(len + 1, sizeof(char));
			ft_strlcpy(tmp, vars->envp[i], len + 1);
			(*arr)[j++] = tmp;
		}
		i++;
	}
}

void	ft_remove_envp(t_vars *vars, char *id)
{
	int		len;
	char	**arr;

	len = ft_envp_len(vars);
	arr = ft_calloc(len, sizeof(char *));
	if (!arr)
		ft_exit(vars, MALLOC_ERROR);
	ft_malloc_envpr(vars, &arr, id);
	if (vars->alloc)
		ft_free_envp(vars->envp);
	vars->envp = arr;
/* 	int	i = 0;
	while (vars->envp[i])
	{
		ft_printf("%s\n", vars->envp[i]);
		i++;
	} */
	if (!vars->alloc)
		vars->alloc = 1;
}
