/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:34:56 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/29 13:01:00 by bpochlau         ###   ########.fr       */
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
	while (prog->heredoc && prog->heredoc[i])
	{
		write(fd, &prog->heredoc[i], 1);
		i++;
	}
	close(fd);
	free (prog->heredoc);
	prog->heredoc = NULL;
}

void	ft_prep_delimiter(t_vars *vars, t_prg *prog)
{
	char	*new;
	char	*str_wo_q;
	int		len;
	int		i;

	prog->hdoc_flag = 0;
	i = -1;
	while (prog->prog[0][++i] && prog->prog[0][i] != ' ' && !prog->hdoc_flag)
		if (prog->prog[0][i] == '\'' || prog->prog[0][i] == '\"')
			prog->hdoc_flag = 1;
	str_wo_q = ft_create_value(vars, prog->prog[0]);
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
	prog->prog[0] = new;
}

void	ft_heredoc_exec(t_vars *vars, t_prg *prog)
{
	char	*str;
	int		len;
	int		j;

	j = 1;
	ft_prep_delimiter(vars, prog);
	len = ft_strlen(prog->prog[0] + 1);
	str = readline("> ");
	if (!str)
		ft_err_m_hered(prog, j);
	while (str && ft_strcmp(str, prog->prog[0]) != 0 && !g_flag)
	{
		j++;
		ft_add_on_heredoc_str(vars, prog, str);
		str = readline("> ");
		if (!str)
			ft_err_m_hered(prog, j);
	}
	if (str)
		free (str);
	if (!prog->hdoc_flag && !g_flag)
		ft_check_enclosing(&prog->heredoc, vars);
	if (!g_flag)
		ft_make_tmp_file(vars, prog);
}

void	ft_heredoc(t_vars *vars, t_prg *prog)
{
	prog->heredoc = NULL;
	signal(SIGINT, ft_handler_child);
	if (ft_check_enclosing_heredoc(prog->prog, vars))
		return ;
	ft_heredoc_exec(vars, prog);
	if (prog->heredoc)
		free (prog->heredoc);
	prog->heredoc = NULL;
	signal(SIGINT, ft_handler_s);
}
