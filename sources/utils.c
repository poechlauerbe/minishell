/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:21:46 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/20 17:01:37 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init(t_vars *vars, int argc, char **argv, char **envp)
{
	ft_bzero(vars, sizeof(t_vars));
	ft_create_env(vars, envp);
	ft_order_envv(vars);
	vars->envp = envp;
	if (argc == 0)
		return ;
	if (argv == 0)
		return ;
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void	ft_set_val(t_vars *vars, t_kv **var, t_kv **tmp)
{
	t_kv	*last;

	(*tmp)->next = NULL;
	ft_add_ao(vars, *tmp);
	if (!(*var))
	{
		(*tmp)->prev = NULL;
		*var = *tmp;
	}
	else
	{
		last = ft_last_entry((*var));
		(*tmp)->prev = last;
		last->next = *tmp;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (1);
	else if (!s2)
		return (-1);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
