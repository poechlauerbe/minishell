/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:46:54 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/29 12:56:59 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_input_strlen_2(char **temp, int *strlen)
{
	while (**temp >= 33 && **temp <= 126 && **temp != '|')
	{
		if (**temp == '\'')
		{
			while (**temp)
			{
				*temp += 1;
				*strlen += 1;
				if (**temp == '\'')
					break ;
			}
		}
		if (**temp == '\"')
		{
			while (**temp)
			{
				*temp += 1;
				*strlen += 1;
				if (**temp == '\"')
					break ;
			}
		}
		*temp += 1;
		*strlen += 1;
	}
}

int	ft_input_strlen(char **inp)
{
	int		strlen;
	char	*temp;

	strlen = 0;
	if (!*inp && !**inp)
		return (strlen);
	while (**inp == ' ' || **inp == '\n' || **inp == '\t'
		|| **inp == '\r' || **inp == '\f' || **inp == '\v'
		|| **inp == '|' || **inp == '<' || **inp == '>')
		*inp += 1;
	temp = *inp;
	ft_input_strlen_2(&temp, &strlen);
	return (strlen);
}

void	ft_copy_progs(t_vars *vars, char **inp, t_prg *temp, char **prog)
{
	int		i;
	int		strlen;
	char	*str;

	i = 0;
	while (i < temp->str_c)
	{
		strlen = ft_input_strlen(inp);
		str = ft_calloc((strlen + 1), sizeof(char));
		if (!str)
		{
			free(prog);
			ft_exit(vars, MALLOC_ERROR);
		}
		ft_strlcpy(str, *inp, strlen + 1);
		prog[i] = str;
		*inp += strlen;
		i++;
	}
	prog[i] = NULL;
}

void	ft_malloc_prog_2d_str(t_vars *vars)
{
	char	**prog;
	char	*inp;
	t_prg	*temp;

	inp = vars->inp;
	temp = vars->p_start;
	while (temp)
	{
		prog = ft_calloc(temp->str_c + 1, sizeof(char *));
		if (!prog)
			ft_exit(vars, MALLOC_ERROR);
		if (*inp == '|')
			inp++;
		ft_copy_progs(vars, &inp, temp, prog);
		temp->prog = prog;
		temp = temp->next;
	}
}
