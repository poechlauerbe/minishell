/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:29:49 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/24 16:19:20 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_malloc_cp(t_vars *vars, char **cp, char *str)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != '\'')
			len++;
	}
	*cp = (char *)calloc(len + 1, sizeof(char));
	if (!*cp)
		ft_exit(vars, MALLOC_ERROR);
	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != '\'')
			(*cp)[len++] = str[i];
	}
	(*cp)[i] = '\0';
}

void	ft_getcwd(t_vars *vars, char **cwd, int *slash, int *cwdlen)
{
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
	{
		err_handler();
		perror("getcwd() error");
		err_handle_free();
		vars->exit_code = 1;
	}
	*cwdlen = ft_strlen(*cwd);
	*slash = 0;
	if ((*cwd) && (*cwd)[*cwdlen - 1] != '/')
		*slash = 1;
}

void	ft_pwd_conc(t_vars *vars, char **curpath)
{
	char	*fpath;
	int		plen;
	int		cwdlen;
	int		slash;
	char	*cwd;

	if (*curpath && (*curpath)[0] != '/')
	{
		plen = ft_strlen(*curpath);
		ft_getcwd(vars, &cwd, &slash, &cwdlen);
		if (!cwd)
			return ;
		fpath = (char *)malloc(sizeof(char) * (plen + cwdlen + slash + 1));
		if (!fpath)
			ft_exit(vars, MALLOC_ERROR);
		ft_strlcpy(fpath, cwd, (cwdlen + 1));
		if (slash)
			ft_strlcat(fpath, "/", cwdlen + 2);
		ft_strlcat(fpath, *curpath, (plen + cwdlen + slash + 1));
		free (*curpath);
		*curpath = fpath;
		if (cwd)
			free (cwd);
	}
}

int	ft_can_form(t_vars *vars, char **curpath)
{
	ft_remove_dot(vars, curpath);
	if (ft_remove_dot_dot(vars, curpath))
	{
		vars->exit_code = 1;
		free (*curpath);
		return (1);
	}
	return (0);
}

void	ft_print_err_cd(t_vars *vars, int error)
{
	err_handler();
	if (error == 1)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	else if (error == 2)
		ft_printf_fd(2, "cd: HOME not set\n");
	err_handle_free();
	vars->exit_code = 1;
}
