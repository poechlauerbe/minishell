/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testbenny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:17:45 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/06 11:06:21 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// int	main(void)
// {
// 	int	fd[2];
// 	int	pid1;
// 	int	pid2;

// 	if (pipe(fd) == -1)
// 		return (PIPE_ERROR);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		return (FORK_ERROR_1);
// 	if (pid1 == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve()
// 		exit(0);
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		return (FORK_ERROR_2);
// 	if (pid2 == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("grep", "grep", "rtt", NULL);
// 		exit(0);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// }

// int main(int argc, char *argv[])
// {
// 	t_vars	vars;
// 	t_prg	*temp;
// 	int		i;

// 	vars.inp = argv[1];
// 	ft_check_input(&vars);
// 	temp = vars.p_start;
// 	while (temp)
// 	{
// 		printf("oper: %c$\n", temp->oper);
// 		i = -1;
// 		while (temp->prog[++i])
// 			printf("string[%i]: %s\n", i, temp->prog[i]);
// 		printf("\n");
// 		temp = temp->next;
// 	}
// }

// int	main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	char	c;
// 	int		i;

// 	fd1 = dup(0);
// 	fd2 = dup(1);
// 	i = 1;
// 	while (i > 0)
// 	{
// 		i = read(fd1, &c, 1);
// 		write(fd2, &c, 1);
// 	}
// 	printf("\nfinished\n");
// }
