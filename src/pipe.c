/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:33:41 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/24 15:15:09 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_exists(char *input)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (input[i])
	{
		if (input[i] == '|')
			pipe_count++;
		i++;
	}
	g_shell.pipe_count = pipe_count;
	return (pipe_count);
}

void	fill_pipeargs(char **pipe_args)
{
	//fills the g_shell.pipeargs array with the pipe_args
	int		i;

	i = 0;
	while(pipe_args[i])
	{
		i++;
		g_shell.pipearg_count++;
	}
	g_shell.pipeargs = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (pipe_args[i])
	{
		g_shell.pipeargs[i] = ft_strdup(pipe_args[i]);
		i++;
	}
	g_shell.pipeargs[i] = NULL;
}

char	**next_pipe_args()
{
	//fills the g_shell.pipeargs array with the pipe_args
	//each time this function called it returns the current pipe args
	//then it increments the g_shell.pipeargs pointer to the next pipe args
	//until it reaches the end of the g_shell.pipeargs array
	
	char	**tmp;
	int		i;
	
	i = 0;
	while(ft_strncmp(g_shell.pipeargs[i], "|", 1) != 0)
		i++;
	tmp = malloc (sizeof(char **) * (i + 1));
	i = 0;
	while(ft_strncmp(g_shell.pipeargs[i], "|", 1) != 0)
	{
		tmp[i] = ft_strdup(g_shell.pipeargs[i]);
		i++;
	}
	tmp[i] = NULL;
	g_shell.pipearg_count = g_shell.pipearg_count - i;
	printf("pipearg_count: %d\n", g_shell.pipearg_count);
	if (g_shell.pipearg_count > 0)
		g_shell.pipeargs = g_shell.pipeargs + i + 1;
	return (tmp);
}

void	init_pipe(char *exec_name, char **pipe_args)
{
	(void)exec_name;
	char **pipe_arg1;
	char **pipe_arg2;
	
	fill_pipeargs(pipe_args);
	pipe_arg1 = next_pipe_args();
	pipe_arg2 = next_pipe_args();
	plumber(pipe_arg1, pipe_arg2);
}

int	plumber(char **pipe_arg1,char **pipe_arg2)
{
	while (g_shell.pipe_count > 0)
	{
		int 	fd[2];
		pid_t 	pid;
		
		if (pipe(fd) == -1) 
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if (pid < 0) 
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) 
		{ // child process
			close(fd[0]); // close read end of the pipe
			dup2(fd[1], STDOUT_FILENO); // redirect stdout to the write end of the pipe
			execute(pipe_arg1[0], pipe_arg1); // execute the first command
			exit(EXIT_FAILURE);
		}
		else 
		{ // parent process
			close(fd[1]); // close write end of the pipe
			pid = fork();
			if (pid < 0) 
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0) 
			{ // child process
				dup2(fd[0], STDIN_FILENO); // redirect stdin to the read end of the pipe
				execute(pipe_arg2[0], pipe_arg2); // execute the second command
				exit(EXIT_FAILURE);
			}
			else 
			{// parent process
				g_shell.pipe_count--;
				close(fd[0]); // close read end of the pipe
				close(fd[1]); // close write end of the pipe
				waitpid(pid, NULL, 0); // wait for the second child process to finish
			}
		}
	}
    return (0);
}
