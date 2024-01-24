/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc_save.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:34:56 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/24 13:21:47 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_name(t_vars *vars, t_red *reds)
{
	char	*num_itoa;

	vars->tmp_count++;
	num_itoa = ft_itoa(vars->tmp_count);
	if (!num_itoa)
		ft_exit(vars, MALLOC_ERROR);
	free(reds->file);
	reds->file = ft_strjoin("/tmp/m_s_h_", num_itoa);
	free(num_itoa);
	if (!reds->file)
		ft_exit(vars, MALLOC_ERROR);
}

void	ft_make_tmp_file(t_vars *vars, t_red *reds)
{
	int	i;
	int	fd;

	ft_create_name(vars, reds);
	fd = open(reds->file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		ft_exit(vars, OPEN_FILE_ERROR);
	write(fd, "\n", 1);
	i = 0;
	while (reds->heredoc && reds->heredoc[i])
	{
		write(fd, &reds->heredoc[i], 1);
		i++;
	}
	close(fd);
	free (reds->heredoc);
	reds->heredoc = NULL;
}

void	ft_prep_delimiter(t_vars *vars, t_red *reds)
{
	char	*new;
	char	*str_wo_q;
	int		len;
	int		i;

	reds->hdoc_flag = 0;
	i = -1;
	while (reds->file[++i] && reds->file[i] != ' ' && !reds->hdoc_flag)
		if (reds->file[i] == '\'' || reds->file[i] == '\"')
			reds->hdoc_flag = 1;
	str_wo_q = ft_create_value(vars, reds->file);
	if (!str_wo_q)
		ft_exit(vars, MALLOC_ERROR);
	free(reds->file);
	reds->file = str_wo_q;
	len = ft_strlen(reds->file);
	new = ft_calloc((len + 2), sizeof(char));
	if (!new)
		ft_exit(vars, MALLOC_ERROR);
	ft_strlcpy(new, reds->file, len + 1);
	free(reds->file);
	new[len] = '\n';
	reds->file = new;
}

void	ft_err_m_hered(t_red *reds, int line_num)
{
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(line_num, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(reds->file, 2);
	ft_putstr_fd("')\n", 2);

}

void	ft_heredoc_exec(t_vars *vars, t_red *reds, int i)
{
	char	*str;
	int		len;
	int		j;

	j = 1;
	signal(SIGINT, ft_handler_child);
	len = ft_strlen(reds->file) + 1;
	str = readline("> ");
	if (!str)
		ft_err_m_hered(reds, j);
	while (str && ft_strncmp(str, reds->file, len) != 0 && !g_flag)
	{
		j++;
		ft_add_on_heredoc_str(vars, reds, str);
		str = readline("> ");
		if (!str)
			ft_err_m_hered(reds, j);
	}
	if (str)
		free (str);
	if (!reds->hdoc_flag)
		ft_check_enclosing(&reds->heredoc, vars);
	if (!g_flag)
		ft_make_tmp_file(vars, reds);
	signal(SIGINT, SIG_DFL);
}
