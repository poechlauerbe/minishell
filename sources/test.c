/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:07:23 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/21 14:02:41 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

/* #include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);
	while (vars.envv)
	{
		printf("%s=%s\n", vars.envv->key, vars.envv->val);
		vars.envv = vars.envv->next;
	}
} */




int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);
	char *inp = "echo ä";
	// ft_printf("%s", inp);
	vars.inp = inp;
	ft_check_input(&vars);
	ft_echo(&vars, vars.p_start->prog);
}
