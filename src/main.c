/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:40 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/26 12:15:05 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
//add cwdr etc. to global variable for the aesthetics. (Done and Done)
//FIX THE AESTHETICS OF THE EXIT COMMAND (done)
// Echo Doesn't prints more than 2 words, i f-ed it up with removing ac, dear future me handle that plox.
// 																			^^ ^ ^^ don't worry kiddo, i gotcha ;) <3
//Add the other commands(done)
//ADD PATH CONTROL TO EXECUTOR <---- DONE BABYBOY, LOVE YA */
//FIX THE WILDCARDS IN MAKEFILE!!!!!!
//FIX THE INFILE OUTCOME
//Refactor
//Add the bonus
//CLEAN UP REDIRECTIONS
//Add the leaks to collector
//Check the norm
//Check the leaks
//Move the files to the right folders and change the makefile
// init_env is not working properly, order is changing while on a new prompt thats called with system call check why
// system call fix the aesthetics, fixed the path for each computer, env order gets f-ed up when this works. 
//Pipe has heap overflow, deal with it, refactor it, make it better, make it work, make it right. And don't forget the Norm <3
//executor, env, redirections, export, collector, command, main norm is not fixed
//make $?  

t_shell	g_shell;


void	read_the_line(char *line, char **linefornow, int ac)
{	
	if (ft_strncmp(line, "exit", 4) == 0)
		exit_minishell(linefornow);
	else if (ft_strncmp(line, "clear", 5) == 0)
		system("clear");
	else if (ft_strncmp(line, "echo", 4) == 0
		|| ft_strncmp(line, "ECHO", 4) == 0)
		echo(ac, linefornow);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(line, "env", 3) == 0 || ft_strncmp(line, "ENV", 3) == 0)
		print_env();
	else if (ft_strncmp(line, "unset", 5) == 0)
		unset_env(linefornow);
	else if (ft_strncmp(line, "export", 6) == 0)
		export_env(linefornow);
	else if (ft_strncmp(line, "cd", 2) == 0)
		change_directory(linefornow);
	else if (redirection_exists(line) == 0)
		redirection_redirector(linefornow);
 	else if (pipe_exists(line) > 0)
		pipe_execute(linefornow);
	else if (if_execexist(linefornow[0]) == 1)
		execute(linefornow[0], linefornow);
	else if (linefornow[0] == NULL)
		return ;
	else
		printf("%s Command not found: %s\n", g_shell.cwdr, line);
}

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
}

void	init_collection(void)
{
	init_env();
	init_collector(&g_shell.collector);
	init_commander(&g_shell.commander);
	init_signal();
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**linefornow;

	open_terminal(av[0]);
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
		linefornow = ft_split(line, ' ');
		add_history(line);
		read_the_line(line, linefornow, ac);
		free(line);
		free(linefornow);
		free(g_shell.cwdr);
	}
	return (0);
}
