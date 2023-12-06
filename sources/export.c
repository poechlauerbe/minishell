/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:22:09 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 16:13:40 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exp_idchecker(char *arg, char *comp)
{
	int	j;

	j = 0;
	if (arg[j] == '\'' || arg[j] == '"')
		j++;
	if (ft_isalpha(arg[j]) || arg[j] == '_')
		j++;
	else
	{
		ft_printf("export: not an identifier: `%s%s'\n", arg, comp);
		return (1);
	}
	while (ft_isalnum(arg[j]))
		j++;
	if (arg[j] == '\'' || arg[j] == '"')
		j++;
	if ((arg[j] != '=' && arg[j] != '\0'))
	{
		ft_printf("export: not an identifier: `%s%s'\n", arg, comp);
		return (1);
	}
	return (0);
}

int	ft_copy_len(char *arg)
{
	int	len;

	len = 0;
	while (*arg && *arg != '=')
	{
		if (*arg != '"' && *arg != '\'')
			len++;
		arg++;
	}
	return (len);
}

char	*ft_copy_id(char *arg)
{
	int		i;
	char	*id;

	id = (char *)malloc(sizeof(char) * (ft_copy_len(arg) + 1));
	if (!id)
	{
		return (NULL);
		ft_putstr_fd("Error allocating memory\n", 2);
	}
	i = 0;
	while (*arg && *arg != '=')
	{
		if (*arg != '\'' && *arg != '"')
		{
			id[i] = *arg;
			i++;
		}
		arg++;
	}
	id[i] = '\0';
	return (id);
}

char	*ft_exp_id(char *arg)
{
	int		len;
	int		j;
	char	*id;
	char	*comp;

	comp = arg;
	while (*comp && (*comp != '=' && *comp != '\0'))
		comp++;
	j = 0;
	len = 0;
	if (arg[len] == '"' || arg[len] == '\'')
	{
		if (ft_check_enclosing(arg))
			return (NULL);
		arg++;
	}
	id = ft_copy_id(arg);
	if (!id)
		return (NULL);
	if (!ft_exp_idchecker(id, comp))
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
			ft_add_envv(vars, id, value);
			free (id);
			free(value);
			i++;
		}
	}
	else
		ft_env(vars);
}
