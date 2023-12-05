/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:22:09 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/05 17:36:41 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* To-Do:
	Check quotes:
		* Single quotes (closed?) --> can copy enclosed stuff;
		*double quotes --> can't copy all symbols;
		*double quotes inside single quotes --> will be printed;
		*single quote inside double quotes: will be printed, but have to be
			stored with escape character;
		*opening and closing quotes won't be printed if the symbols are not
		special symbols;
		otherwise the value is stored with singel quotes
	shorten or outsource to other functions
 */

int	ft_exp_idchecker(char *arg)
{
	int	j;

	j = 0;
	if (ft_isalpha(arg[j]))
		j++;
	else
	{
		ft_printf("export: not an identifier: %s", arg);
		return (1);
	}
	while (ft_isalnum(arg[j]))
		j++;
	if ((arg[j] != '=' && arg[j] != '\0'))
	{
		ft_printf("export: not valid in this context: %s", arg);
		return (1);
	}
	return (0);
}

char	*ft_exp_identifier(char *arg)
{
	int		len;
	int		j;
	char	*id;

	j = 0;
	len = 0;
	if (arg[len] == '"' || arg[len] == '\'')
	{
		ft_check_quotes(arg);
		arg++;
	}

	while (arg[len] && arg[len] != '=' && arg[len] != '"' && arg[len] != '\'')
		len++;
	id = (char *)malloc(sizeof(char) * (len + 1));
	if (!id)
		return (NULL);
	len = 0;
	while (arg[len] && arg[len] != '=')
	{
		id[len] = arg[len];
		len++;
	}
	id[len] = '\0';
	if (!ft_exp_idchecker(id))
		return (id);
	else
	{
		free(id);
		return (NULL);
	}
}

/* before using the function --> if (ft_strcmp(vars->p_start->prog[i][0],
	"export"));
	passing i and j to function?
*/
void	ft_export(t_prg prg)
{
	int		j;
	char	*str;
	char	*id;
	char	*value;

	// have to check all the arguments, there can be several assignments in one program export a=1 b=2 c=3
	str = vars->p_start->prog[1];
	if (str)
	{
		id = ft_exp_identifier(str);
		if (!id)
			return ;
		value = ft_exp_value(str);
		//create key value pair

		// check other arguments if they
		return (0);
	}
	else
		ft_env(vars);
}
