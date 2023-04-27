/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:47:16 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 21:06:16 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append(char **args)
{
	append_init();
	while (args[g_shell.redir3.i] != NULL)
	{
		if (strcmp(args[g_shell.redir3.i], ">>") == 0)
		{
			g_shell.redir3.filename = args[g_shell.redir3.i + 1];
			args[g_shell.redir3.i] = NULL;
			break ;
		}
		g_shell.redir3.i++;
	}
	g_shell.redir3.file_desc = open(g_shell.redir3.filename, O_WRONLY
			| O_APPEND | O_CREAT, 0644);
	g_shell.redir3.pid = fork();
	if (g_shell.redir3.pid == -1)
		exit(1);
	else if (g_shell.redir3.pid == 0)
	{
		if (dup2(g_shell.redir3.file_desc, STDOUT_FILENO) == -1)
			exit(1);
		close(g_shell.redir3.file_desc);
		execute(args[0], args);
		exit(1);
	}
	waitpid(g_shell.redir3.pid, &g_shell.redir3.status, 0);
}

void	outfile_childe(char **args)
{
	int		i;
	char	*output;
	int		fd;

	i = 0;
	output = NULL;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], ">", 1) == 0)
		{
			output = args[i + 1];
			args[i] = NULL;
			break ;
		}
		i++;
	}
	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	execute(args[0], args);
	exit(EXIT_FAILURE);
}

void	outfile(char **args)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		outfile_childe(args);
	else
		waitpid(pid, &status, 0);
}
