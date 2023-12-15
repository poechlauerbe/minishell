#include "inc/minishell.h"

void	ft_quit_dot(t_vars *vars, char **curpath)
{
	int		len;
	int		i;
	char	*temp;

	i = -1;
	len = 0;
	while (*curpath[++i])
	{
		if (*curpath[i] == '.' && *curpath[i + 1] == '/')
			i++;
		else
			len++;
		}
	temp = (char *)malloc(sizeof(char) * (len + 1));
	i = -1;
	len = 0;
	while (*curpath[++i])
	{
		if (*curpath[i] == '.' && *curpath[i + 1] == '/')
			i++;
		else
			temp[len] = *curpath[i];
	}
	free (*curpath);
	*curpath = temp;
}

int	main(void)
{
	int		i = 0;
	char	*curpath;
	char	*test = "test/./test/./test/./";
	t_vars	vars;

	ft_init(&vars, 0, NULL, NULL);
	curpath = (char *)malloc(sizeof(char) * 30);
	while (*test)
	{
		curpath[i++] = *test;
		test++;
	}
	curpath[i] = '\0';
	ft_quit_dot(&vars, &curpath);
	ft_printf("%s", curpath);
}
