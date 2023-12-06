/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:22:09 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 13:43:02 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exp_idchecker(char *arg)
{
	int	j;

	j = 0;
	if (ft_isalpha(arg[j]) || arg[j] == '_')
		j++;
	else
	{
		ft_printf("export: not an identifier: %s", arg);
		return (1);
	}
	while (ft_isalnum(arg[j]))
		j++;
	if ((arg[j] != '=' && arg[j] != '\0'))
	{
		ft_printf("export: not valid in this context: %s", arg);
		return (1);
	}
	return (0);
}

char	*ft_exp_id(char *arg)
{
	int		len;
	int		j;
	char	*id;

	j = 0;
	len = 0;
	if (arg[len] == '"' || arg[len] == '\'')
	{
		if (ft_check_enclosing(arg))
			return (NULL);
		arg++;
	}
	while (arg[len] && arg[len] != '=' && arg[len] != '"' && arg[len] != '\'')
		len++;
	id = (char *)malloc(sizeof(char) * (len + 1));
	if (!id)
		return (NULL);
	len = 0;
	while (arg[len] && arg[len] != '=')
	{
		id[len] = arg[len];
		len++;
	}
	id[len] = '\0';
	if (!ft_exp_idchecker(id))
		return (id);
	else
	{
		free(id);
		return (NULL);
	}
}

void	ft_export(t_vars *vars)
{
	int		i;
	char	*str;
	char	*id;
	char	*value;

	i = 1;
	if (vars->p_start->prog[i])
	{
		while (vars->p_start->prog[i])
		{
			str = vars->p_start->prog[i];
			id = ft_exp_id(str);
			if (!id)
				return ;
			value = ft_exp_value(str);
			if (!value)
				return ;
			ft_printf("%s=%s\n", id, value);
			// ft_add_envv(vars, id, value);
			free (id);
			free(value);
			i++;
		}
	}
	else
		ft_env(vars);
}
