#include "minishell.h"

//Unsets the environment variable
void	unset_env(char *unsettling)
{
	int		i;
	int		j;

	i = 0;
	while (shell.environments[i])
	{
		if (ft_strncmp(shell.environments[i], unsettling, ft_strlen(unsettling)) == 0)
		{
			free(shell.environments[i]);
			j = i;
			while (shell.environments[j])
			{
				shell.environments[j] = shell.environments[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}