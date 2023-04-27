/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:40 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 23:17:01 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
//FIX THE WILDCARDS IN MAKEFILE!!!!!!
//Refactor
//Add the leaks to collector
//Check the norm
//Check the leaks
//Move the files to the right folders and change the makefile
//collector, command, main norm is not fixed*/
/* ************************************************************************** */

t_shell	g_shell;

void	open_terminal(char *av)
{
	char **args;

	args = malloc(sizeof(char *) * 5);
	args[0] = "/usr/bin/open";
	args[1] = "-a";
	args[2] = "Terminal.app";
	args[3] = "./minishell";
	args[4] = NULL;
	if (ft_strncmp(av, "./minishell", 11) == 0)
	{
		execve(args[0], args, NULL);
		free(args);
		exit (0);
	}
}

void	flush_the_terminal(void)
{
	printf("\033[1;1H\033[2J");
	g_shell.exit_status = 0;
}

void	init_collection(void)
{
	init_env();
	init_collector(&g_shell.collector);
	init_commander(&g_shell.commander);
	init_signal();
}

void	read_the_line(char *line, char **linefornow)
{	
	if (linefornow[0] == NULL)
		return ;
	else if (check_syntax_redir(linefornow) == 0)
		return ;
 	else if (linefornow[0][0] == '\0')
	{
		printf("%s Command not found:\n", g_shell.cwdr);
		g_shell.exit_status = 127;
	}
	else if (check_exit_status(linefornow) == 0 || check_syntax_builtin(linefornow) == 0)
		return ;
	else if (redirection_exists(line) == 0)
		redirection_redirector(linefornow);
 	else if (pipe_exists(line) == 0)
		pipe_execute(linefornow);
	else if (ft_strncmp(linefornow[0], "clear", 5) == 0)
		flush_the_terminal();
	else if (if_execexist(linefornow[0]) == 1)
		execute(linefornow[0], linefornow);
	else
	{
		printf("%s Command not found: %s\n", g_shell.cwdr, line);
		g_shell.exit_status = 127;
	}
}


int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**linefornow;

	// open_terminal(av[0]);
	(void)ac;
	(void)av;
	(void)envp;
	init_collection();
	flush_the_terminal();
	while (true)
	{
		g_shell.cwdr = ft_strjoin(getcwd(NULL, 0), " | minishell> ");
		line = readline(g_shell.cwdr);
		if (line == NULL)
		{
			printf("%s exit", g_shell.cwdr);
			exit(0);
		}
		linefornow = lexer(line);
		add_history(line);
		read_the_line(line, linefornow);
		free(line);
		free(linefornow);
		free(g_shell.cwdr);
	}
	return (0);
}
