#include "minishell.h"

char	*get_env_var(char *var_name)
{
	int		i;
	char	*var;

	i = 0;
	while (shell.environments[i])
	{
		if (ft_strncmp(shell.environments[i], var_name, ft_strlen(var_name)) == 0)
		{
			var = ft_substr(shell.environments[i], ft_strlen(var_name) + 1, ft_strlen(shell.environments[i]));
			return (var);
		}
		i++;
	}
	return (NULL);
}

char	*getfullpath(char *path, char *c, char *exec_name)
{
	char	*semi_path;
	char	*full_path;

	semi_path = ft_strjoin(path, c);
	full_path = ft_strjoin(semi_path, exec_name);
	return (full_path);
}

int	ifexecist(char *exec_name)
{
	char	*path;
	char	*full_path;
	char	*path_var;
	char	**path_list;
	int		i;

	path_var = get_env_var("PATH");
	if (!path_var)
		return (-1);
	path_list = ft_split(path_var, ':');
	i = 0;
	while (path_list[i] && path_list[i] != NULL)
	{
		path = path_list[i];
		full_path = getfullpath(path, "/", exec_name);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

//execute with execve and fork - Check the return value of execve and print the error message accordingly
int	execute(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			if (ifexecist(args[0]) == 1)
				printf("minishell: permission denied: %s\n", args[0]);
			else
				printf("minishell: command not found: %s\n", args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("minishell");
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
