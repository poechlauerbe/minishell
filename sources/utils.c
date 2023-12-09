/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:21:46 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/09 12:50:35 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init(t_vars *vars, int argc, char **argv, char **envp)
{
	ft_bzero(vars, sizeof(t_vars));
	argc = 0;
	argv = NULL;
	ft_create_env(vars, envp);
	ft_order_envv(vars);
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
	if (ft_strncmp(vars->inp, "export", 6) == 0)
		ft_export(vars);
	if (ft_strncmp(vars->p_start->prog[0], "echo", 4) == 0)
		ft_echo(vars->p_start->prog);
	if (ft_strncmp(vars->inp, "env", 3) == 0)
		ft_env(vars);
	if (ft_strncmp(vars->inp, "unset", 5) == 0)
		ft_unset(vars);
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void	ft_set_val(t_vars *vars, t_kv **var, t_kv **tmp, char *key, char *val)
{
	t_kv	*last;

	(*tmp)->key = key;
	(*tmp)->val = val;
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
