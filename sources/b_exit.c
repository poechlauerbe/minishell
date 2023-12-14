/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:12:25 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/14 12:06:32 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_endof_atoi(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\r' || nptr[i] == '\f' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		i ++;
	return (i);
}

void	ft_exit_prog(t_vars *vars, char **prog)
{
	int		num;
	char	*str_wo_q;

	if (prog[1] && prog[2])
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
	else if (prog[1])
	{
		str_wo_q = ft_create_value(vars, prog[1]);
		if (!str_wo_q)
			ft_exit(vars, MALLOC_ERROR);
		if (str_wo_q[ft_endof_atoi(str_wo_q)])
			ft_printf_fd(2, "exit\nbash: exit: %s: numeric argument required\n",
				prog[1]);
		else
		{
			num = ft_atoi(prog[1]);
			while (num >= 256)
				num -= 256;
			while (num < 0)
				num += 256;
			ft_exit(vars, num);
		}
	}
	else
		ft_exit(vars, OK);
}
