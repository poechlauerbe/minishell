/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:28:25 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/29 14:36:03 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	err_mes(int errcd)
{
	ft_putstr_fd("Error\n", 2);
	ft_putnbr_fd(errcd, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_free_reds(t_red **file)
{
	t_red	*temp;
	t_red	*next;

	temp = *file;
	while (temp)
	{
		next = temp;
		if (temp->file)
			free(temp->file);
		// free(temp);
		if (temp == *file)
			*file = NULL;
		temp = next;
	}
}

void	ft_free_input(t_vars *vars)
{
	t_prg	*temp;
	t_prg	*temp2;
	char	**prog;
	int		i;

	temp = vars->p_start;
	// if (vars->inp)
	// 	free(vars->inp);
	while (temp)
	{
		prog = temp->prog;
		temp2 = temp->next;
		// printf("%s")
		// if (temp->in_file)
		// 	ft_free_reds(&temp->in_file);
		// if (temp->out_file)
		// 	ft_free_reds(&temp->out_file);
		i = 0;
		while (prog && prog[i])
		{
			free(prog[i]);
			i++;
		}
		if (prog)
			free(prog);
		if (temp)
			free(temp);
		temp = temp2;
	}
	vars->p_start = NULL;
}

void	ft_free_envv(t_vars *vars)
{
	t_kv	*tmp;

	while (vars->envv)
	{
		tmp = vars->envv->next;
		if (vars->envv->key)
			free (vars->envv->key);
		if (vars->envv->val)
			free (vars->envv->val);
		free (vars->envv);
		vars->envv = tmp;
	}
}

void	ft_exit(t_vars *vars, int errcd)
{
	if (errcd > 256)
		err_mes(errcd);
	// else
	// 	ft_putstr_fd("exit\n", 2);
	ft_free_input(vars);
	// ft_free_envv(vars);
	exit(errcd);
}

int	ft_reset(t_vars *vars)
{
	ft_free_input(vars);
	return (1);
}
