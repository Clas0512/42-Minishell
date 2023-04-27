/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:28:30 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 19:33:07 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_childe(char **args, const char *tmp_filename)
{
	int	input_fd;

	input_fd = open(tmp_filename, O_RDONLY);
	if (input_fd == -1)
		exit(1);
	if (dup2(input_fd, STDIN_FILENO) == -1)
		exit(1);
	close(input_fd);
	execute(args[0], args);
	exit(1);
}

void	heredoc_write(void)
{
	write(g_shell.redir2.tmp_fd,
		g_shell.redir2.line, ft_strlen(g_shell.redir2.line));
	write(g_shell.redir2.tmp_fd, "\n", 1);
	free(g_shell.redir2.line);
	printf("> ");
}

void	heredoc(char **args, char *delimiter)
{
	g_shell.redir2.tmp_filename = "/tmp/heredoc.tmp";
	g_shell.redir2.tmp_fd = open(g_shell.redir2.tmp_filename,
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	g_shell.redir2.delimiter_found = 0;
	printf("> ");
	g_shell.redir2.line = readline(NULL);
	while (g_shell.redir2.line != NULL)
	{
		g_shell.redir2.line = readline(NULL);
		if (ft_strncmp(g_shell.redir2.line,
				delimiter, ft_strlen(delimiter)) == 0)
		{
			g_shell.redir2.delimiter_found = 1;
			free(g_shell.redir2.line);
			break ;
		}
		heredoc_write();
	}
	close(g_shell.redir2.tmp_fd);
	g_shell.redir2.pid = fork();
	if (g_shell.redir2.pid == 0)
		heredoc_childe(args, g_shell.redir2.tmp_filename);
	else
		waitpid(g_shell.redir2.pid, &g_shell.redir2.status, 0);
	unlink(g_shell.redir2.tmp_filename);
}
