/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 05:01:52 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 19:30:54 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//FIX THE INFILE OUTCOME

int	redirection_exists(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<' )
			return (0);
		i++;
	}
	return (1);
}

char	*her_delim(char **linefornow)
{
	int		i;
	char	*delim;

	i = 0;
	delim = NULL;
	while (linefornow[i])
	{
		if (ft_strncmp(linefornow[i], "<<", 2) == 0)
		{
			delim = ft_strdup(linefornow[i + 1]);
			break ;
		}
		i++;
	}
	return (delim);
}

char	**her_sep(char **linefornow)
{
	int		i;
	int		j;
	char	**heredoc;

	i = 0;
	j = 0;
	while (linefornow[i])
	{
		if (ft_strncmp(linefornow[i], "<<", 2) == 0)
			j = i;
		i++;
	}
	heredoc = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (linefornow[++i])
	{
		if (i == j)
			break ;
		heredoc[i] = ft_strdup(linefornow[i]);
	}
	heredoc[i] = NULL;
	return (heredoc);
}

void	redirection_redirector(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], ">>", 2) == 0)
		{
			append(args);
			break ;
		}
		else if (ft_strncmp(args[i], "<<", 2) == 0)
		{
			heredoc(her_sep(args), her_delim(args));
			break ;
		}
		else if (ft_strncmp(args[i], ">", 1) == 0)
			outfile(args);
		else if (ft_strncmp(args[i], "<", 1) == 0)
			infile(args);
		i++;
	}
}

void	infile(char **args)
{
	redir_init();
	while (args[++g_shell.redir.i] != NULL)
	{
		if (ft_strncmp(args[g_shell.redir.i], "<", 1) == 0)
		{
			g_shell.redir.filename = args[g_shell.redir.i + 1];
			args[g_shell.redir.i] = NULL;
			break ;
		}
	}
	g_shell.redir.pid = fork();
	if (g_shell.redir.pid < 0)
		exit(EXIT_FAILURE);
	else if (g_shell.redir.pid == 0)
	{
		g_shell.redir.fd = open(g_shell.redir.filename, O_RDONLY);
		if (g_shell.redir.fd < 0)
			exit(EXIT_FAILURE);
		g_shell.redir.result = dup2(g_shell.redir.fd, STDIN_FILENO);
		if (g_shell.redir.result < 0)
			exit(EXIT_FAILURE);
		execute(args[0], args);
	}
	else
		waitpid(g_shell.redir.pid, &g_shell.redir.status, 0);
}
