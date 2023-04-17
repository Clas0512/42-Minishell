#include "minishell.h"

void	pwd()
{
	int		i;
	char 	**envtmp;

	i = 0;
	envtmp = shell.environments;
	while (envtmp[i] != NULL)
	{
		if (ft_strncmp(envtmp[i], "PWD=", 4) == 0)
		{
			printf("%s \n", envtmp[i]);
			return ;
		}
		i++;
	}
}

char	*get_pwd()
{
	int		i;
	size_t		j;
	char	**envtmp;
	char	*pwd;

	i = 0;
	j = 0;
	envtmp = shell.environments;
	while (envtmp[i] != NULL)
	{
		if (ft_strncmp(envtmp[i], "PWD=", 4) == 0)
		{
			pwd = malloc(sizeof(char) * (ft_strlen(envtmp[i]) - 3));
			while (j < ft_strlen(envtmp[i]) - 4)
			{
				pwd[j] = envtmp[i][j + 4];
				j++;
			}
			pwd[j] = '\0';
			return (pwd);
		}
		i++;
	}
	return (NULL);
}
