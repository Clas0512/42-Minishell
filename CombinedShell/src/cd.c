#include "minishell.h"

//changes directory, gets the path from the environment variables
void	cd(char **path)
{
	char	*temp;
	int		i;

	i = 0;
	if (path[1] == NULL)
	{
		while (shell.environments[i])
		{
			if (ft_strncmp(shell.environments[i], "HOME=", 5) == 0)
			{
				temp = ft_substr(shell.environments[i], 5, ft_strlen(shell.environments[i]));
				chdir(temp);
				return ;
			}
			i++;
		}
	}
}
