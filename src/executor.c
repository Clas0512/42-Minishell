/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:36 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/23 14:52:49 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_variable(char *var_name)
{
	int		i;
	char	*var;
	char	*temp;

	i = 0;
	while (g_shell.environments[i])
	{
		temp = g_shell.environments[i];
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
	if (exec_name == NULL)
		return (0);
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

char	*return_exec_path(char *exec_name)
{
	char	*path;
	char	*full_path;
	char	*path_var;
	char	**path_list;
	int		i;

	path_var = get_env_variable("PATH");
	if (!path_var)
		return ("Path not found.");
	path_list = ft_split(path_var, ':');
	i = 0;
	while (path_list[i] && path_list[i] != NULL)
	{
		path = path_list[i];
		full_path = get_full_path(path, "/", exec_name);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (0);
}

char	**combine_path_and_args(char *full_path_to_exec, char **args)
{
	char	**path_and_args;
	int		i;
	int		j;

	i = 0;
	j = (ft_strlen(full_path_to_exec) + ft_strlen(args[0]) + 1);
	path_and_args = malloc(sizeof(char *) * j);
	path_and_args[i] = ft_strdup(full_path_to_exec);
	i++;
	while (args[i])
	{
		path_and_args[i] = ft_strdup(args[i]);
		i++;
	}
	path_and_args[i] = NULL;
	return (path_and_args);
}

int	execute(char *exec_name, char **args)
{
	pid_t	pid;
	int		wstatus;
	int		statuscode;
	char	*full_path_to_exec;
	char	**path_and_args; 

	if (if_execexist(exec_name) == 1)
	{
		full_path_to_exec = return_exec_path(exec_name);
		path_and_args = combine_path_and_args(full_path_to_exec, args);
		pid = fork();
		if (pid == 0)
		{
			if (execve(full_path_to_exec, path_and_args, NULL) == -1)
			{
				if (if_execexist(exec_name) == 1)
					printf("%s Permission Denied : %s\n", g_shell.cwdr, exec_name);
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
				printf("%s %d: %s: %s\n", g_shell.cwdr, statuscode, exec_name, strerror(statuscode));
				return (1);
			}
		}
	}
	else
		printf("%s: %s: command not found : %s\n", g_shell.cwdr, exec_name, strerror(127));
	return (0);
}
