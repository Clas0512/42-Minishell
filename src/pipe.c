/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:33:41 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 13:36:31 by anargul          ###   ########.fr       */
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
			return (0);
		i++;
	}
	return (1);
}

void	child_proc()
{
	int	i;

	i = 0;
	if (g_shell.pipe.pipe_idx > 0)
		dup2(g_shell.pipe.pipes[(g_shell.pipe.pipe_idx - 1) * 2], STDIN_FILENO);
	if (g_shell.pipe.pipe_idx < g_shell.pipe.num_pipes)
		dup2(g_shell.pipe.pipes[g_shell.pipe.pipe_idx * 2 + 1], STDOUT_FILENO);
	while (i < g_shell.pipe.num_pipes * 2)
	{
		close (g_shell.pipe.pipes[i]);
		i++;
	}
	if (execute(g_shell.pipe.args[0], g_shell.pipe.args) != 0)
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}

void	parent_proc()
{
	int	wstatus;

	if (g_shell.pipe.pipe_idx > 0)
		close(g_shell.pipe.pipes[(g_shell.pipe.pipe_idx - 1) * 2]);
	if (g_shell.pipe.pipe_idx < g_shell.pipe.num_pipes)
		close(g_shell.pipe.pipes[g_shell.pipe.pipe_idx * 2 + 1]);
	if (waitpid(g_shell.pipe.pid, &wstatus, 0) < 0)
	{
		if (WIFEXITED(wstatus))
			g_shell.exit_status = WEXITSTATUS(wstatus);
		else
			g_shell.exit_status = 0;
	}
}

void	pipe_execute_init(int mod)
{
	if (mod == 1)
		g_shell.pipe.pipes = malloc(sizeof(int) * g_shell.pipe.num_pipes * 2);
	else
	{
		g_shell.pipe.num_pipes = 0;
		g_shell.pipe.pipeargs_idx = 0;
		g_shell.pipe.args = NULL;
		g_shell.pipe.start = 0;
		g_shell.pipe.end = 0;
		g_shell.pipe.pipe_idx = 0;
		g_shell.pipe.i = 0;
	}
}

void	pipe_execute(char **pipeargss)
{
	pipe_execute_init(0);
	while (pipeargss[g_shell.pipe.pipeargs_idx] != NULL)
	{
		if (ft_strncmp(pipeargss[g_shell.pipe.pipeargs_idx], "|", 1) == 0)
			g_shell.pipe.num_pipes++;
		g_shell.pipe.pipeargs_idx++;
	}
	pipe_execute_init(1);
	while (g_shell.pipe.i < g_shell.pipe.num_pipes)
	{
		if (pipe(g_shell.pipe.pipes + g_shell.pipe.i * 2) < 0)
			return ;
		g_shell.pipe.i++;
	}
	while (pipeargss[g_shell.pipe.end] != NULL)
	{
		while (pipeargss[g_shell.pipe.end] != NULL
			&& ft_strncmp(pipeargss[g_shell.pipe.end], "|", 1) != 0)
			g_shell.pipe.end++;
		g_shell.pipe.args = malloc(sizeof(char *) * (g_shell.pipe.end - g_shell.pipe.start + 1));
		g_shell.pipe.i = g_shell.pipe.start;
		while (g_shell.pipe.i < g_shell.pipe.end)
		{
			g_shell.pipe.args[g_shell.pipe.i - g_shell.pipe.start] = pipeargss[g_shell.pipe.i];
			g_shell.pipe.i++;
		}
		g_shell.pipe.args[g_shell.pipe.end - g_shell.pipe.start] = NULL;
		g_shell.pipe.pid = fork();
		if (g_shell.pipe.pid < 0)
			return ;
		else if (g_shell.pipe.pid == 0)
			child_proc();
		else
			parent_proc();
		g_shell.pipe.start = g_shell.pipe.end + 1;
		if (pipeargss[g_shell.pipe.end] != NULL)
			g_shell.pipe.end = g_shell.pipe.start;
		g_shell.pipe.pipe_idx++;
	}
	return ;
}