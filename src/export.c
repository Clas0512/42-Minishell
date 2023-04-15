#include "minishell.h"
// change free's with collector cleaner
//add to collector

//export command for shell with no options
void	export(char **newenvname)
{
	t_shell tempenv;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (shell.environments[i])
		i++;
	tempenv.environments = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shell.environments[i])
	{
		tempenv.environments[i] = ft_strdup(shell.environments[i]);
		i++;
	}
	tempenv.environments[i] = ft_strdup(newenvname[1]);
	tempenv.environments[i + 1] = NULL;
	j = 0;
	while (shell.environments[j])
	{
		free(shell.environments[j]);
		j++;
	}
	free (shell.environments);
	shell.environments = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tempenv.environments[i])
	{
		shell.environments[i] = ft_strdup(tempenv.environments[i]);
		i++;
	}
	shell.environments[i] = NULL;
	i = 0;
	while (tempenv.environments[i])
	{
		free(tempenv.environments[i]);
		i++;
	}
	free(tempenv.environments);
}
