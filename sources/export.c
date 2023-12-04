/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:22:09 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/04 16:35:23 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_exp_value(char *arg)
{
	char	*value;
	int		i;

	while (*arg != '=' && *arg != '\0')
		arg++;
	if (*arg == '\0')
	{
		value = (char *)malloc(sizeof(char) * 2);
		value[0] = '';
		value[1] = '\0';
	}
	else
	{
		arg++;
		i = 0;
		if (arg[i] == '\'' || arg[i] == '"')
			arg++;
		value = (char *)malloc(sizeof(char) * (ft_strlen(arg) + 1));
		while (arg[i])
			value[i] = arg[i];
		arg[i] = '\0'
	}
	return (value);
}

int	ft_idchecker(char *arg)
{
	int	j;

	j = 0;
	if (ft_isalpha(arg[j]))
			j++;
	else
	{
		ft_printf("export: not an identifier: %s", arg);
		return (1);
	}
	while(ft_isalnum(arg[j]))
		j++;
	if ((arg[j] != '=' && arg[j] != '\0'))
	{
		ft_printf("export: not valid in this context: %s", arg);
		return (1);
	}
	return (0);
}

char	*ft_exp_identifier(char *arg)
{
	int		len;
	int		j;
	char	*id;

	j = 0;
	len = 0;
	if (arg[len] == '"' || arg[len] == '\'')
		arg++;
	// needs test if quotes close at the end;
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
	if (!ft_idchecker(id))
		return (id);
	else
	{
		free(id);
		return (NULL);
	}
}

/* before using the function --> if (ft_strcmp(vars->p_start->prog[i][0], "export"));
	passing i and j to function?
*/
void	ft_export(t_vars *vars, int i)
{
	int		j;
	char	*str;
	char	*id;
	char	*value;

	// check if after export there is an assignment of a variable
	str = vars->p_start->prog[1];
	if (str)
	{
		id = ft_exp_identifier(str);
		if (!id)
			return ;
		value = ft_exp_value(str);
		// test for validity of input with quotes
		//create key value pair
		else
		{
			ft_printf("export: not valid in this context: %s", id);
			free(id);
			return ;
		}
		return (0);
	}
	else
		ft_env(vars);
}
