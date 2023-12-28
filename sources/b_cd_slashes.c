/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_slashes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:11:52 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/14 15:07:04 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_remove_trails(t_vars *vars, char **cp)
{
	size_t		len;
	char		*tmp;

	len = ft_strlen(*cp) - 1;
	while ((*cp)[len] == '/')
		len--;
	if (len != (ft_strlen(*cp) - 1))
	{
		tmp = ft_substr(*cp, 0, (len + 1));
		if (!tmp)
			ft_exit(vars, MALLOC_ERROR);
		free (*cp);
		*cp = tmp;
	}
}

int	ft__remove_nl_len(char *cp)
{
	int	len;

	len = 0;
	while (*cp == '/')
	{
		len++;
		cp++;
	}
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

void	ft_remove_nls(t_vars *vars, char **cp)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = ft__remove_nl_len(*cp);
	tmp = (char *)calloc((len + 1), sizeof(char));
	if (!tmp)
		ft_exit(vars, MALLOC_ERROR);
	i = 0;
	j = 0;
	while ((*cp)[i] == '/')
		tmp[j++] = (*cp)[i++];
	while ((*cp)[i])
	{
		while ((*cp)[i] == '/' && (*cp)[i + 1] == '/')
			i++;
		tmp[j++] = (*cp)[i];
		i++;
	}
	tmp[j] = '\0';
	free (*cp);
	*cp = tmp;
}

void	ft_remove_ls(t_vars *vars, char **cp)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*cp)[len] == '/')
		len++;
	if (len >= 3)
	{
		tmp = ft_substr(*cp, (len - 1), ft_strlen(*cp));
		if (!tmp)
			ft_exit(vars, MALLOC_ERROR);
		free (*cp);
		*cp = tmp;
	}
}

void	ft_remove_slashes(t_vars *vars, char **cp)
{
	ft_remove_trails(vars, cp);
	ft_remove_nls(vars, cp);
	ft_remove_ls(vars, cp);
}
