/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:07:23 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/30 12:51:50 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
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


/* int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
/nfs/homes/tbenz/Desktop/42 Core Curriculum
	ft_init(&vars, argc, argv, envp);
	while (vars.envv)
	{
		printf("%s=%s\n", vars.envv->key, vars.envv->val);
		vars.envv = vars.envv->next;
	}
} */

/* int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	ft_init(&vars, argc, argv, envp);
	char *inp = "cd /nfs/homes/tbenz/Desktop";
	// ft_printf("%s", inp);
	vars.inp = inp;
	ft_check_input(&vars);
	ft_builtin_check(&vars, vars.p_start);
	char *inp2 = "cd \"42 Core Curriculum\"";
	vars.inp = inp2;
	ft_check_input(&vars);
	ft_builtin_check(&vars, vars.p_start);
	ft_exit(&vars, OK);
} */
