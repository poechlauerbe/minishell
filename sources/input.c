/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:30:48 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/07 17:51:03 by bpochlau         ###   ########.fr       */
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
		|| **inp == '\r' || **inp == '\f' || **inp == '\v'
		|| **inp == '|' || **inp == '<' || **inp == '>')
		*inp += 1;
	temp = *inp;
	while (*temp >= 33 && *temp <= 126 && *temp != '|')
	{
		// if (*temp == '<' || *temp == '>' )
		// 	break;
		if (*temp == '\'')
		{
			while (*temp)
			{
				temp++;
				strlen++;
				if (*temp == '\'')
					break ;
			}
			// if (*temp == '\0')
			// 	return (OPEN_QUOTES);
		}
		if (*temp == '\"')
		{
			while (*temp)
			{
				temp++;
				strlen++;
				if (*temp == '\"')
					break ;
			}
			// if (*temp == '\0')
			// 	return (OPEN_QUOTES);
		}
		strlen++;
		temp++;
	}
	return (strlen);
}

void	ft_malloc_prog_2d_str(t_vars *vars)
{
	char	**prog;
	char	*str;
	char	*inp;
	int		strlen;
	int		i;
	t_prg	*temp;

	inp = vars->inp;
	temp = vars->p_start;
	while (temp)
	{
		prog = ft_calloc(temp->str_c + 1, sizeof(char *));
		if (!prog)
			ft_exit(vars, MALLOC_ERROR);
		i = 0;
		if (*inp == '|')
			inp++;
		while (i < temp->str_c)
		{
			strlen = ft_input_strlen(&inp);
			str = malloc((strlen + 1) * sizeof(char));
			if (!str)
				ft_exit(vars, MALLOC_ERROR);
			ft_strlcpy(str, inp, strlen + 1);
			prog[i] = str;
			inp += strlen;
			i++;
		}
		prog[i] = NULL;
		temp->prog = prog;
		temp = temp->next;
	}
}

void	ft_check_string_count(t_vars *vars, char *inp)
{
	t_prg	*temp;

	// if (!inp || !*inp)
	// 	ft_reset();
	vars->p_start = malloc(sizeof(t_prg));
	if (!vars->p_start)
		ft_exit(vars, MALLOC_ERROR);
	vars->p_start->next = NULL;
	vars->p_start->oper = '0';
	temp = vars->p_start;
	temp->str_c = 0;
	while (*inp)
	{
		while (*inp == ' ' || *inp == '\n' || *inp == '\t'
			|| *inp == '\r' || *inp == '\f' || *inp == '\v')
			inp++;
		if (*inp >= 33 && *inp <= 126 && *inp != '|' && *inp != '<' && *inp != '>')
		{
			if ((temp->oper == '<' || temp->oper == '>') && temp->str_c == 1)
				ft_new_node(vars, &temp, &inp);
			temp->str_c += 1;
		}
		while (*inp >= 33 && *inp <= 126)
		{
			if (*inp == '\'' || *inp == '\"')
				ft_check_quotes(&inp);
			if (*inp == '|' || *inp == '<' || *inp == '>')
			{
				ft_new_node(vars, &temp, &inp);
				break ;
			}
			inp++;
		}
	}
}

void	ft_red_file(t_vars *vars, t_prg *lst)
{
	t_prg	*prog;
	t_prg	*temp;
	int		inp_files;
	int		out_files;
	int		i;
	int		j;

	temp = lst;
	inp_files = 0;
	out_files = 0;
	prog = NULL;
	while (temp->oper != '|')
	{
		if (temp->oper == '0')
			prog = temp;
		else if (temp->oper == '>')
			out_files++;
		else if (temp->oper == '<')
			inp_files++;
		temp = temp->next;
	}
	if (inp_files > 0)
	{
		// init in init function (= NULL)
		prog->in_file = malloc((inp_files + 1) * sizeof(char *));
		if (!prog->in_file)
			ft_exit(vars, MALLOC_ERROR);
		prog->in_file[inp_files] = NULL;
	}
	if (out_files > 0)
	{
		// init in init function (= NULL)
		prog->out_file = malloc((out_files + 1) * sizeof(char *));
		if (!prog->out_file)
			ft_exit(vars, MALLOC_ERROR);
		prog->out_file[out_files] = NULL;
	}
	i = 0;
	j = 0;
	while (temp->oper != '|')
	{
		if (temp->oper == '>')
			prog->out_file[i++] = temp->prog[0];
		else if (temp->oper == '<')
			prog->in_file[j++] = temp->prog[0];
		temp = temp->next;
	}
	if (access())
}

void	ft_check_input(t_vars *vars)
{
	ft_check_string_count(vars, vars->inp);
	ft_malloc_prog_2d_str(vars);
	ft_cleanup_lst(vars);
	ft_red_file(vars, vars->p_start);

}
