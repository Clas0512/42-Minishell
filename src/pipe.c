/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:33:41 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/26 23:56:29 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_exists(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	child_proc(char **args, int *pipes, int pipe_idx, int num_pipes)
{
	int	i;

	i = 0;
	if (pipe_idx > 0)
		dup2(pipes[(pipe_idx - 1) * 2], STDIN_FILENO);
	if (pipe_idx < num_pipes)
		dup2(pipes[pipe_idx * 2 + 1], STDOUT_FILENO);
	while (i < num_pipes * 2)
	{
		close (pipes[i]);
		i++;
	}
	if (execute(args[0], args) != 0)
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}

void	parent_proc(int *pipes, int pipe_idx, int num_pipes, pid_t pid)
{
	int	wstatus;

	if (pipe_idx > 0)
		close(pipes[(pipe_idx - 1) * 2]);
	if (pipe_idx < num_pipes)
		close(pipes[pipe_idx * 2 + 1]);
	if (waitpid(pid, &wstatus, 0) < 0)
	{
		if (WIFEXITED(wstatus))
			g_shell.exit_status = WEXITSTATUS(wstatus);
		else
			g_shell.exit_status = 0;
	}
}

void	pipe_execute(char **pipeargss)
{
	int		num_pipes;
	int		pipeargs_idx;
	int		pipe_idx;
	int		start;
	int		end;
	int		i;
	char	**args;
	pid_t	pid;

	num_pipes = 0;
	pipeargs_idx = 0;
	args = NULL;
	while (pipeargss[pipeargs_idx] != NULL)
	{
		if (ft_strncmp(pipeargss[pipeargs_idx], "|", 1) == 0)
			num_pipes++;
		pipeargs_idx++;
	}
	int	pipes[num_pipes * 2];//BERKE
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes + i * 2) < 0)
			return ;
		i++;
	}
	start = 0;
	end = 0;
	pipe_idx = 0;
	while (pipeargss[end] != NULL)
	{
		while (pipeargss[end] != NULL
			&& ft_strncmp(pipeargss[end], "|", 1) != 0)
			end++;
		args = malloc(sizeof(char *) * (end - start + 1));
		i = start;
		while (i < end)
		{
			args[i - start] = pipeargss[i];
			i++;
		}
		args[end - start] = NULL;
		pid = fork();
		if (pid == 0)
			child_proc(args, pipes, pipe_idx, num_pipes);
		else
			parent_proc(pipes, pipe_idx, num_pipes, pid);
		start = end + 1;
		if (pipeargss[end] != NULL)
			end = start;
		pipe_idx++;
	}
}
