/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:30:48 by bpochlau          #+#    #+#             */
/*   Updated: 2023/11/30 12:54:33 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_input_strlen(char **inp)
{
	int		strlen;
	char	*temp;

	strlen = 0;
	if (!*inp && !**inp)
		return (strlen);
	while (**inp == ' ' || **inp == '\n' || **inp == '\t'
		|| **inp == '\r' || **inp == '\f' || **inp == '\v')
		*inp += 1;
	temp = *inp;
	while (*temp >= 33 && *temp <= 126)
	{
		// if (*temp == '|' || *temp == '<' || *temp == '>' )
		// 	break;
		strlen++;
		temp++;
	}
	return (strlen);
}

void	ft_malloc_prog_2d_str(t_vars *vars, int str_c)
{
	char	**prog;
	char	*str;
	char	*inp;
	int		strlen;
	int		i;

	inp = vars->inp;
	prog = malloc(sizeof(char *) * (str_c + 1));
	// if (!prog)
	// 	ft_exit();
	ft_bzero(prog, sizeof(char *) * (str_c + 1));
	i = 0;
	while (i < str_c)
	{
		strlen = ft_input_strlen(&inp);
		str = malloc((strlen + 1) * sizeof(char));
		// if (!str)
		// 	ft_exit();
		ft_strlcpy(str, inp, strlen + 1);
		vars->p_start->prog[i] = str;
		inp += strlen;
		i++;
	}
}

void	ft_check_string_count(t_vars *vars, char *inp, int *str_c)
{
	// if (!inp || !*inp)
	// 	ft_reset();
	vars->p_start = malloc(sizeof(t_prg));
	// if (!var->p_start)
	// 	ft_exit();
	vars->p_start->next = NULL;
	*str_c = 0;
	while (*inp)
	{
		while (*inp == ' ' || *inp == '\n' || *inp == '\t'
			|| *inp == '\r' || *inp == '\f' || *inp == '\v')
			inp++;
		if (*inp >= 33 && *inp <= 126)
			*str_c += 1;
		while (*inp >= 33 && *inp <= 126)
		{
			// if (*inp == '|' || *inp == '<' || *inp == '>' )
			// 	break;
			inp++;
		}
	}
}

void	ft_check_input(t_vars *vars)
{
	int	str_c;

	ft_check_string_count(vars, vars->inp, &str_c);
	ft_malloc_prog_2d_str(vars, str_c);

}
