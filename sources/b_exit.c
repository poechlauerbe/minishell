/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:12:25 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/19 19:02:04 by bpochlau         ###   ########.fr       */
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

long long	ft_atoi_ll(const char *nptr, int *err)
{
	long long	sign;
	long long	sum;

	sign = 1;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			sign *= -1;
		nptr++;
	}
	sum = 0;
	while (*nptr > 47 && *nptr < 58)
	{
		if (sum > LONG_MAX / 10
			|| (sum == LONG_MAX / 10 && sign == 1 && *nptr > '7')
			|| (sum == LONG_MAX / 10 && sign == -1 && *nptr > '8'))
		{
			*err = 1;
			return (1);
		}
		sum *= 10;
		sum += (*nptr - '0');
		nptr++;
	}
	return (sum * sign);
}

void	ft_err_mes_numeric(char *prog)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	ft_calc_exit_code(t_vars *vars, char *str_wo_q, char *prog)
{
	long long	num;
	int			err;
	int			i;

	err = OK;
	i = 0;
	while (str_wo_q[i] == 32 || (str_wo_q[i] > 8 && str_wo_q[i] < 14))
		i++;
	num = ft_atoi_ll(&str_wo_q[i], &err);
	num %= 256;
	if (num < 0)
		num += 256;
	if (err == OK)
	{
		free(str_wo_q);
		ft_exit(vars, num);
	}
	else
		ft_err_mes_numeric(prog);
}

void	ft_exit_prog(t_vars *vars, char **prog)
{
	char	*str_wo_q;

	if (prog[1])
	{
		str_wo_q = ft_create_value(vars, prog[1]);
		if (!str_wo_q)
			ft_exit(vars, MALLOC_ERROR);
		if (str_wo_q[0] == '\0' || str_wo_q[ft_endof_atoi(str_wo_q)])
		{
			ft_err_mes_numeric(prog[1]);
			free(str_wo_q);
			ft_exit(vars, SYNTAX_ERROR);
		}
		else if (prog[1] && prog[2])
		{
			ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
			vars->exit_code = 1;
		}
		else
			ft_calc_exit_code(vars, str_wo_q, prog[1]);
		free(str_wo_q);
	}
	else
		ft_exit(vars, vars->exit_code);
}
