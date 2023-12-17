/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testbenny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:17:45 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/15 08:10:20 by bpochlau         ###   ########.fr       */
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

int main(int argc, char *argv[])
{
	t_vars	vars;
	t_prg	*temp;
	int		i;

	if (argc == 1)
		return (256);
	vars.inp = argv[1];
	vars.exit_code = 99;
	ft_check_input(&vars);
	ft_pipe_loop(&vars);
	temp = vars.p_start;
	while (temp)
	{
		printf("oper: %c$\n", temp->oper);
		i = -1;
		while (temp->prog[++i])
			printf("string[%i]: %s\n", i, temp->prog[i]);
		printf("\n");
		while(temp->out_file)
		{
			printf("in: %s, %c$\n", temp->out_file->file, temp->out_file->oper);
			temp->out_file = temp->out_file->next;
		}
		temp = temp->next;
	}
	// ft_exit(&vars, OK);
}

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

// int	ft_pipe(t_vars *vars)
// {
// 	int		fd[2];
// 	int		pid1;
// 	int		pid2;
// 	t_prg	*temp;

// 	temp = vars->p_start;
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
// 		execve(temp->prog[0], temp->prog, NULL);
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		return (FORK_ERROR_2);
// 	if (pid2 == 0)
// 	{
// 		temp = temp->next;
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve(temp->prog[0], temp->prog, NULL);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	if (waitpid(pid1, NULL, 0) == -1)
// 		return (WAITPID_ERROR);
// 	if (waitpid(pid2, NULL, 0) == -1)
// 		return (WAITPID_ERROR);
// 	return (OK);
// }

	// i = 0;
	// while (i < count_pipe && pid[i] != 0)
	// {
	// 	pid[++i] = fork();
	// }
