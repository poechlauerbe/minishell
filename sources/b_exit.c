/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:12:25 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/19 18:31:11 by bpochlau         ###   ########.fr       */
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
	printf("test2");
	while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			sign *= -1;
		nptr++;
	}
	printf("test3");
	sum = 0;
	while (*nptr > 47 && *nptr < 58)
	{
		if (sum > LONG_MAX / 10)
		// 	|| (sum == LONG_MAX / 10 && sign == 1 && *nptr > '7')
		// 	|| (sum == LONG_MAX / 10 && sign == -1 && *nptr > '8'))
		{
			*err = 1;
			return (1);
		}
		*err = OK;
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

	err = OK;
	printf("test1");
	num = ft_atoi_ll(str_wo_q, &err);
	while (num >= 256)
		num -= 256;
	while (num < 0)
		num += 256;
	if (err == OK)
	{
		printf("test1");
		free(str_wo_q);
		ft_exit(vars, (int)num);
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
