/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_dotdot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:28:33 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/08 17:39:27 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_test_dir(t_vars *vars, char **cp, int i)
{
	char	*dir;
	int		j;

	if (!ft_strcmp(*cp, "//") || !ft_strcmp(*cp, "/.."))
		return (0);
	dir = (char *)calloc((i + 1), sizeof(char));
	if (!dir)
		ft_exit(vars, MALLOC_ERROR);
	j = -1;
	while (++j < i)
		dir[j] = (*cp)[j];
	dir[j] = '\0';
	if (access(dir, F_OK))
	{
		free(dir);
		free (*cp);
		ft_printf_fd(2, "cd: No such file or directory: %s\n", \
					vars->p_start->prog[1]);
		return (1);
	}
	free (dir);
	return (0);
}

void	ft_create_cp2(char **cp, int cl, int i, char **tmp)
{
	int	j;
	int	k;

	k = -1;
	j = ft_dot_dot_len(*cp, i);
	while ((*cp)[++k] && k <= (i - cl))
		(*tmp)[k] = (*cp)[k];
	i += j;
	while ((*cp)[i])
	{
		(*tmp)[k++] = (*cp)[i];
		i++;
	}
	(*tmp)[k] = '\0';
}

void	ft_create_cp(t_vars *vars, char **cp, int i, int cl)
{
	size_t	len;
	char	*temp;

	len = ft_strlen(*cp) - cl - ft_dot_dot_len(*cp, i);
    if (!i && !ft_strcmp(*cp, "/.."))
        temp = ft_substr(*cp, 0, 1);
	else if (i == 1)
	{
		len = ft_dot_dot_len(*cp, 0);
		if (len == ft_strlen(*cp))
			temp = ft_substr(*cp, 0, 1);
		else
			temp = ft_substr(*cp, (len - 1), ft_strlen(*cp));
	}
	else
	{
    	temp = (char *)ft_calloc((len + 2), sizeof(char));
        if (!temp)
            ft_exit(vars, MALLOC_ERROR);
		ft_create_cp2(cp, cl, i, &temp);
    }
	free (*cp);
	*cp = temp;
}

int	ft_remove_dd2(t_vars *vars, char **temp, int i)
{
	int	cl;

    cl = 0;
	while ((*temp)[++i] && strcmp(*temp, "/"))
	{
		if (!ft_strncmp(&((*temp)[i]), "/../", 4) ||
			!ft_strncmp(&((*temp)[i]), "/..\0", 4))
		{
			if (i > 0 && ft_test_dir(vars, temp, i))
				return (1);
			ft_create_cp(vars, temp, i, cl);
			i = -1;
            cl = 0;
		}
		if (i > 0 && (i == 0 || (*temp)[i - 1] == '/'))
			cl = ft_remove_dd_currlen(*temp, i);
	}
	return (0);
}

int	ft_remove_dot_dot(t_vars *vars, char **cp)
{
	int		i;
	char	*temp;
    char    *tmp;

	i = 0;
	while (cp[0][i + 1] == '/')
		i++;
	temp = ft_substr(*cp, i, (ft_strlen(*cp) - i));
	if (!temp)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	if (ft_remove_dd2(vars, &temp, i))
		return (1);
    if (ft_strlen(temp) > 1 && (temp)[ft_strlen(temp) - 1] == '/'
		&& temp[ft_strlen(temp) - 2] != '/')
	{
		tmp = ft_substr(temp, 0, strlen(temp) - 1);
		if (!tmp)
			ft_exit(vars, MALLOC_ERROR);
		free (temp);
		temp = tmp;
	}
	free (*cp);
	*cp = temp;
	return (0);
}
