/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:34:56 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/07 18:09:49 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_name(t_vars *vars, t_prg *prog)
{
	char	*num_itoa;

	vars->tmp_count++;
	num_itoa = ft_itoa(vars->tmp_count);
	if (!num_itoa)
		ft_exit(vars, MALLOC_ERROR);
	free(prog->prog[0]);
	prog->prog[0] = ft_strjoin("/tmp/m_s_h_", num_itoa);
	free(num_itoa);
	if (!prog->prog[0])
		ft_exit(vars, MALLOC_ERROR);
}

void	ft_make_tmp_file(t_vars *vars, t_prg *prog)
{
	int	i;
	int	fd;

	ft_create_name(vars, prog);
	fd = open(prog->prog[0], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		ft_exit(vars, OPEN_FILE_ERROR);
	i = 0;
	while (prog->heredoc[i])
	{
		write(fd, &prog->heredoc[i], 1);
		i++;
	}
	close(fd);
	free (prog->heredoc);
}

void	ft_prep_delimiter(t_vars *vars, t_prg *prog)
{
	char	*new;
	char	*str_wo_q;
	int		len;
	int		i;

	prog->hdoc_flag = 0;
	i = 0;
	while (prog->prog[0][i] && prog->prog[0][i] != ' ' && !prog->hdoc_flag)
	{
		if (prog->prog[0][i] == '\'' || prog->prog[0][i] == '\"')
			prog->hdoc_flag = 1;
		i++;
	}
	str_wo_q = ft_create_value(vars, prog->prog[0]);
	// ft_printf("%s\n", str_wo_q);
	if (!str_wo_q)
		ft_exit(vars, MALLOC_ERROR);
	free(prog->prog[0]);
	prog->prog[0] = str_wo_q;
	len = ft_strlen(prog->prog[0]);
	new = ft_calloc((len + 2), sizeof(char));
	if (!new)
		ft_exit(vars, MALLOC_ERROR);
	ft_strlcpy(new, prog->prog[0], len + 1);
	free(prog->prog[0]);
	new[len] = '\n';
	prog->prog[0] = new;
}

void	ft_heredoc_exec(t_vars *vars, t_prg *prog)
{
	char	*str;
	char	*temp;
	int		len;

	prog->heredoc = NULL;
	ft_prep_delimiter(vars, prog);
	len = ft_strlen(prog->prog[0]);
	// write(2, ">", 1);
	str = get_next_line(0);
	while (ft_strncmp(str, prog->prog[0], len) != 0)
	{
		if (prog->heredoc)
		{
			temp = NULL;
			temp = ft_substr(prog->heredoc, 0, ft_strlen(prog->heredoc));
			if (!temp)
				ft_exit(vars, MALLOC_ERROR);
			free(prog->heredoc);
			prog->heredoc = ft_strjoin(temp, str);
			if (!prog->heredoc)
				ft_exit(vars, MALLOC_ERROR);
			free (temp);
		}
		else
		{
			prog->heredoc = ft_substr(str, 0, strlen(str));
			if (!prog->heredoc)
				ft_exit(vars, MALLOC_ERROR);
		}
		if (str)
			free (str);
		// write(2, ">", 1);
		str = get_next_line(0);
	}
	if (str)
		free (str);
	if (!prog->hdoc_flag)
		ft_check_enclosing(&prog->heredoc, vars);
	ft_make_tmp_file(vars, prog);
}

void	ft_heredoc(t_vars *vars)
{
	t_prg	*prog;

	prog = vars->p_start;
	while (prog)
	{
		if (prog->oper == O_HEREDOC)
			ft_heredoc_exec(vars, prog);
		prog = prog->next;
	}
}
