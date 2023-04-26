/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:36 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/26 18:20:06 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (exec_name == NULL)
		return (0);
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
	char	**path_and_args;

	path_and_args = combine_path_and_args(return_exec_path(exec_name), args);
	pid = fork();
	if (pid == 0)
	{
		if (execve(return_exec_path(exec_name), path_and_args, NULL) == -1)
		{
			if (if_execexist(exec_name) == 1)
				printf("%s Permission Denied : %s\n", g_shell.cwdr, exec_name);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("Child Process Failed.");
	else
	{
		waitpid(pid, &wstatus, WUNTRACED);
		g_shell.statuscode = WEXITSTATUS(wstatus);
		printf("Exit status: %d, statuscode = %d\n", WEXITSTATUS(wstatus), g_shell.statuscode);
		if (WIFEXITED(wstatus) && WIFSIGNALED(wstatus))
			return (1);
	}
	return (0);
}
