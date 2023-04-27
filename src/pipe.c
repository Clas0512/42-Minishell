/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:33:41 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 10:33:05 by anargul          ###   ########.fr       */
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

void	pipe_execute_init()
{
	g_shell.pipe.num_pipes = 0;
	g_shell.pipe.pipeargs_idx = 0;
	g_shell.pipe.args = NULL;
	g_shell.pipe.start = 0;
	g_shell.pipe.end = 0;
	g_shell.pipe.pipe_idx = 0;
	g_shell.pipe.i = 0;
}

int	pipe_execute(char **pipeargss)
{
	pipe_execute_init();
	while (pipeargss[g_shell.pipe.pipeargs_idx] != NULL)
	{
		if (ft_strncmp(pipeargss[g_shell.pipe.pipeargs_idx], "|", 1) == 0)
			g_shell.pipe.num_pipes++;
		g_shell.pipe.pipeargs_idx++;
	}
	int	pipes[g_shell.pipe.num_pipes * 2];
	while (g_shell.pipe.i < g_shell.pipe.num_pipes)
	{
		if (pipe(pipes + g_shell.pipe.i * 2) < 0)
			return (-1);
		g_shell.pipe.i++;
	}
	while (pipeargss[g_shell.pipe.end] != NULL)
	{//Find the g_shell.pipe.end of the curr comm
		while (pipeargss[g_shell.pipe.end] != NULL && ft_strncmp(pipeargss[g_shell.pipe.end], "|", 1) != 0)
			g_shell.pipe.end++;
		//Set up the args for the curr comm
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
			return (-1);
		else if (g_shell.pipe.pid == 0)
		{// Childé
			if (g_shell.pipe.pipe_idx > 0)// Set up input redir from the prev comm
			{
				if (dup2(pipes[(g_shell.pipe.pipe_idx-1)*2], STDIN_FILENO) < 0)
					return (-1);
			}
			if (g_shell.pipe.pipe_idx < g_shell.pipe.num_pipes)// Set up outp redir to the next comm
			{
				if (dup2(pipes[g_shell.pipe.pipe_idx*2+1], STDOUT_FILENO) < 0)
					return (-1);
			}
			g_shell.pipe.i = 0;
			while (g_shell.pipe.i < g_shell.pipe.num_pipes * 2)
			{
				close (pipes[g_shell.pipe.i]);
				g_shell.pipe.i++;
			}
			if (execute(g_shell.pipe.args[0], g_shell.pipe.args) != 0)
				exit (EXIT_FAILURE);
			exit (EXIT_SUCCESS);
		}
		else
		{//Par.proc.
			if (g_shell.pipe.pipe_idx > 0)//Close the inp g_shell.pipe.end of the prev pipe
				close(pipes[(g_shell.pipe.pipe_idx-1)*2]);
			if (g_shell.pipe.pipe_idx < g_shell.pipe.num_pipes)// Close the outp g_shell.pipe.end of the curr pipe
				close(pipes[g_shell.pipe.pipe_idx*2+1]);
			if (waitpid(g_shell.pipe.pid, &g_shell.pipe.wstatus, 0) < 0)
				return (-1);
			if (WIFEXITED(g_shell.pipe.wstatus) && WEXITSTATUS(g_shell.pipe.wstatus) != 0)
				return (-1);
		}
		g_shell.pipe.start = g_shell.pipe.end + 1;
		if (pipeargss[g_shell.pipe.end] != NULL)
			g_shell.pipe.end = g_shell.pipe.start;
		g_shell.pipe.pipe_idx++;
	}
	return (0);
}
