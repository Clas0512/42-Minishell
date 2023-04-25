/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:33:41 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/23 15:27:30 by aerbosna         ###   ########.fr       */
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
	return (pipe_count);
}

void	init_pipe(char *exec_name, char **pipe_args)
{
	char	**tmp;
	int		i;

	//fill tmp with pipe_args arguments until | is found
	i = 0;
	while (pipe_args[i] && *pipe_args[i] != '|')
	{
		i++;
	}
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (pipe_args[i] && *pipe_args[i] != '|')
	{
		tmp[i] = ft_strdup(pipe_args[i]);
		i++;
	}
	tmp[i] = NULL;
	while (1)
	{
		plumber(exec_name, tmp);
		break;
	}
}

int	plumber(char *exec_name, char **pipe_args)
{
    int 	fd[2];
    pid_t 	pid;
    char	*cmd2[] = {"wc", "-l", NULL};
	
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // child process
        close(fd[0]); // close read end of the pipe
        dup2(fd[1], STDOUT_FILENO); // redirect stdout to the write end of the pipe
        execute(exec_name, pipe_args); // execute the first command
        exit(EXIT_FAILURE);
    }
    else { // parent process
        close(fd[1]); // close write end of the pipe
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) { // child process
            dup2(fd[0], STDIN_FILENO); // redirect stdin to the read end of the pipe
            execute(cmd2[0], cmd2); // execute the second command
            exit(EXIT_FAILURE);
        }
        else { // parent process
            waitpid(pid, NULL, 0); // wait for the second child process to finish
        }
    }

    return 0;
}
