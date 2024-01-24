/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_mes_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:10:19 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/24 14:18:34 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	err_handler(void)
{
	int	fd;

	fd = -1;
	while (fd < 0)
		fd = open("/tmp/ms_136", O_RDWR | O_EXCL | O_CREAT, 0644);
	// if (!vars->fd_errmes)
	// 	ft_exit(vars, OPEN_FILE_ERROR);
	close(fd);
}

void	err_handle_free(void)
{
	unlink("/tmp/ms_136");
}
