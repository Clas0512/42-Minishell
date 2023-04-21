/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:36 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/21 19:40:49 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ADD PATH CONTROL

char	*get_env_variable(char *var_name)
{
	int		i;
	char	*var;
	char	*temp;

	i = 0;
	while (shell.environments[i])
	{
		temp = shell.environments[i];
		if (ft_strncmp(temp, var_name, ft_strlen(var_name)) == 0)
		{
			var = ft_substr(temp, ft_strlen(var_name) + 1, ft_strlen(temp));
			return (var);
		}
		i++;
	}
	return (NULL);
}

char	*get_full_path(char *path, char *c, char *exec_name)
{
	char	*semi_path;
	char	*full_path;

	semi_path = ft_strjoin(path, c);
	full_path = ft_strjoin(semi_path, exec_name);
	return (full_path);
}

int	if_execexist(char *exec_name)
{
	char	*path;
	char	*full_path;
	char	*path_var;
	char	**path_list;
	int		i;

	path_var = get_env_variable("PATH");
	if (!path_var)
		return (-1);
	path_list = ft_split(path_var, ':');
	i = 0;
	while (path_list[i] && path_list[i] != NULL)
	{
		path = path_list[i];
		full_path = get_full_path(path, "/", exec_name);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute(char *exec_name, char **args)
{
	pid_t	pid;
	int		wstatus;
	int		statuscode;

	pid = fork();
	if (pid == 0)
	{
		if (execve(exec_name, args, NULL) == -1)
		{
			if (if_execexist(exec_name) == 1)
				printf("%s Permission Denied : %s\n", shell.cwdr, exec_name);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Child Process Failed.");
	}
	else
	{
		waitpid(pid, &wstatus, WUNTRACED);
		if (WIFEXITED(wstatus) && WIFSIGNALED(wstatus))
		{
			statuscode = WEXITSTATUS(wstatus);
			printf("minishell: %d: %s: %s\n", statuscode, exec_name, strerror(statuscode));
			return (1);
		}
	}
	return (0);
}
