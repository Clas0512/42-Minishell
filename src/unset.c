#include "minishell.h"

//Unsets the environment variable
void	unset_env(char **unsettling)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(unsettling[1]);
	while (shell.environments[i])
	{
		if (ft_strncmp(shell.environments[i], unsettling[1], j) == 0)
		{
			while (shell.environments[i])
			{
				shell.environments[i] = shell.environments[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}
