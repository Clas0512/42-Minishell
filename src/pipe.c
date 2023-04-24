/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:33:41 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/25 00:23:56 by aerbosna         ###   ########.fr       */
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

int	pipe_execute(char **pipeargss)
{
	int		num_pipes;
	int		pipeargs_idx;
	int		pipe_idx;
	int		wstatus;
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
		{
			num_pipes++;
		}
		pipeargs_idx++;
	}
	int	pipes[num_pipes * 2];
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes + i * 2) < 0)
		{
			perror ("pipe");
			return (-1);
		}
		i++;
	}
	start = 0;
	end = 0;
	pipe_idx = 0;
	while (pipeargss[end] != NULL)
	{//Find the end of the curr comm
		while (pipeargss[end] != NULL && ft_strncmp(pipeargss[end], "|", 1) != 0)
			end++;
		//Set up the args for the curr comm
		args = malloc(sizeof(char *) * (end - start + 1));
		i = start;
		while (i < end)
		{
			args[i-start] = pipeargss[i];
			i++;
		}
		args[end-start] = NULL;
		pid = fork();
		if (pid < 0)
			return (-1);
		else if (pid == 0)
		{// Childé
			if (pipe_idx > 0)// Set up input redir from the prev comm
			{
				if (dup2(pipes[(pipe_idx-1)*2], STDIN_FILENO) < 0)
					return (-1);
			}
			if (pipe_idx < num_pipes)// Set up outp redir to the next comm
			{
				if (dup2(pipes[pipe_idx*2+1], STDOUT_FILENO) < 0)
					return (-1);
			}
			i = 0;
			while (i < num_pipes * 2)
			{
				close (pipes[i]);
				i++;
			}
			if (execute(args[0], args) != 0)
				exit (EXIT_FAILURE);
			exit (EXIT_SUCCESS);
		}
		else
		{//Par.proc.
			if (pipe_idx > 0)//Close the inp end of the prev pipe
				close(pipes[(pipe_idx-1)*2]);
			if (pipe_idx < num_pipes)// Close the outp end of the curr pipe
				close(pipes[pipe_idx*2+1]);
			if (waitpid(pid, &wstatus, 0) < 0)
			{
				perror ("waitpid");
				return (-1);
			}
			if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
				return (-1);
		}
		start = end + 1;
		end = start;
		pipe_idx++;
	}
	return (0);
}
