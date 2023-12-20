/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:07:23 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/20 13:42:28 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* int main (void)
{
	char	*path = "/bin/ls";
	char	*argv[] = {"/bin/ls", "-lsa", NULL};

	execve(path, argv, NULL);
} */

// #include <stdio.h>


// int main(void) {
//  char *args[] = {"/bin/ls", "-lsa", NULL};
//  execve(args[0], args, NULL);
//  return 0;
// }

#include "../inc/minishell.h"

/* int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);

} */

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	// t_kv	*first;

	ft_init(&vars, argc, argv, envp);
	ft_order_envv(&vars);
	ft_new_envp(&vars, "eins", "1");
	ft_new_envp(&vars, "zwei", "2");
	envp = vars.envp;
	int	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	ft_printf("\n\n\n");
	ft_remove_envp(&vars, "MAIL");
	envp = vars.envp;
	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	ft_remove_envp(&vars, "zwei");
	envp = vars.envp;
	ft_printf("\n\n\n");
	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
/* 	ft_add_envv(&vars, "HANS", "eins", 1);
	char *input_new = {"export HANS"};
	vars.inp = input_new;
	ft_check_input(&vars);
	ft_input(&vars);
	ft_free_input(&vars);
	char *input_new2 = {"export"};
	vars.inp = input_new2;
	ft_check_input(&vars);
	ft_input(&vars); */
	ft_free_envp(vars.envp);
	ft_exit(&vars, OK);
}
