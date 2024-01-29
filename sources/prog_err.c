/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:56:05 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/29 11:54:20 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_no_rights(t_vars *vars, char *prog, char *to_free)
{
	err_handler();
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	err_handle_free();
	if (to_free)
		free(to_free);
	ft_exit(vars, 126);
}

void	ft_is_dir(t_vars *vars, t_prg *prog)
{
	err_handler();
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(prog->prog[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	err_handle_free();
	vars->exit_code = 126;
	ft_exit(vars, 126);
}

void	ft_prog_not_found(t_vars *vars, t_prg *prog)
{
	struct stat	fileinfo;

	ft_printf("%s", prog->prog[0]);
	if (stat(prog->prog[0], &fileinfo) == 0 && (ft_strcmp(prog->prog[0], ".")
			&& ft_strcmp(prog->prog[0], "..")))
	{
		if (S_ISDIR(fileinfo.st_mode))
			ft_is_dir(vars, prog);
		else if (!access(prog->prog[0], F_OK) && !ft_return_val(vars, "PATH"))
			ft_no_rights(vars, prog->prog[0], NULL);
	}
	else
	{
		err_handler();
		ft_putstr_fd(prog->prog[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		err_handle_free();
		vars->exit_code = 127;
		ft_exit(vars, 127);
	}
}
