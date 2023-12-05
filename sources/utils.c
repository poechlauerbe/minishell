/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:21:46 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/05 14:03:05 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init(t_vars *vars, int argc, char **argv, char **envp)
{
	ft_bzero(vars, sizeof(t_vars));
	argc = 0;
	argv = NULL;
	vars->envp = envp;
}

void	ft_input(t_vars *vars)
{
	if (!vars->inp)
		exit(EOF + 128);
	else if (ft_strlen(vars->inp) > 0)
		add_history(vars->inp);
	if (ft_strncmp(vars->inp, "exit", 4) == 0)
		exit(0);
	if (ft_strncmp(vars->inp, "pwd", 3) == 0)
		ft_pwd();
	if (ft_strncmp(vars->p_start->prog[0], "echo", 4) == 0)
		ft_echo(vars->p_start->prog);
	if (ft_strncmp(vars->inp, "env", 3) == 0)
		ft_env(vars);
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
