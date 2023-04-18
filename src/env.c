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

char *get_env(char *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = ft_strlen(env);
	tmp = NULL;
	while (shell.environments[i])
	{
		if (ft_strncmp(shell.environments[i], env, ft_strlen(env)) == 0)
		{
			tmp = ft_strdup(shell.environments[i]);
			i = 0;
			while (tmp[i] != '\0' && tmp[i + j] != '\0')
			{
				tmp[i] = tmp[i + j];
				i++;
			}
			tmp[i + j] = '\0';
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

//set_env
//sets the environment variable to the shell.environments
//why the f*ck i did added the last line?
void	set_env(char *env, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (shell.environments[i])
	{
		if (ft_strncmp(shell.environments[i], env, ft_strlen(env)) == 0)
		{
			printf("found %s\n", shell.environments[i]);
			tmp = ft_strjoin(env, str);
			free(shell.environments[i]);
			shell.environments[i] = tmp;
//			printf("found %s\n", shell.environments[i]);
			return ;
		}
		i++;
	}
	//shell.environments[i] = ft_strdup(env);
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
