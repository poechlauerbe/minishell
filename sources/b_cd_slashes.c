/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_slashes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:11:52 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/13 18:38:28 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_remove_trail(t_vars *vars, char **cp)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*cp);
	while ((*cp)[len] == '/')
		len--;
	if (len != ft_strlen(*cp))
	{
		tmp = ft_substr(*cp, 0, len);
		free (cp);
		cp = tmp;
	}
}

int	ft__remove_nl_len(t_vars *vars, char *cp)
{
	int	i;
	int	len;

	i = 0;
	while (*cp == '/')
		len++;
	while (*cp)
	{
		if (*cp == '/' && *(cp + 1) == '/')
			cp++;
		else
		{
			len++;
			cp++;
		}
	}
	return (len);
}

void	ft_remove_nl(t_vars *vars, char **cp)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = ft__remove_nl_len(vars, *cp);
	tmp = (char *)calloc((len + 1), sizeof(char));
	if (!tmp)
		ft_exit(vars, MALLOC_ERROR);
	i = 0;
	while ((*cp)[i] == '/')
		i++;
	j = 0;
	while ((*cp)[i])
	{
		if ((*cp)[i] == '/' && (*cp)[i + 1] == '/')
		{
			while ((*cp)[i] == '/')
				i++;
		}
		else
			tmp[j++] = (*cp)[i];
		i++;
	}
	tmp[j] = '\0';
	free (*cp);
	*cp = tmp;
}

void	ft_remove_slashes(t_vars *vars, char **cp)
{
	ft_remove_trails(vars, cp);
	ft_remove_nls(vars, cp);
	ft_remove_ls(vars, cp);
}
