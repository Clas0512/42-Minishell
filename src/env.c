#include "minishell.h"

void	print_env()
{
	int	i;

	i = 0;
	while (shell.environments[i])
	{
		printf("%s\n", shell.environments[i]);
		i++;
	}
}
//extend global**
//init getenv
//Initializes the environment variables to struct
//fill the shell.environments with the getenv

//get all the environments from getenv and fill the shell.environments with it
void	init_env(void)
{
	int		i;
	char	*env;
	extern char **environ;

	i = 0;
	while (environ[i])
		i++;
	shell.environments = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		env = ft_strdup(environ[i]);
		shell.environments[i] = env;
		i++;
	}
	shell.environments[i] = NULL;
}
