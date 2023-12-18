/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:07:23 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/18 16:44:17 by tbenz            ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	*inp = "~/bpocahlau";

	ft_init(&vars, argc, argv, envp);
	vars.inp = inp;
	ft_check_input(&vars);
	ft_home_expand(&vars, &vars.p_start->prog[0]);
	ft_printf("%s\n", vars.p_start->prog[0]);
	ft_free_input(&vars);
}

/*
	Thorben test env-key values
int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	// t_kv	*first;

	ft_init(&vars, argc, argv, envp);
	ft_order_envv(&vars);
	ft_add_envv(&vars, "HANS", "eins", 1);
	char *input_new = {"export HANS"};
	vars.inp = input_new;
	ft_check_input(&vars);
	ft_input(&vars);
	ft_free_input(&vars);
	char *input_new2 = {"export"};
	vars.inp = input_new2;
	ft_check_input(&vars);
	ft_input(&vars);
}
*/
