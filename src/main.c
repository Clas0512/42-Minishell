/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:40 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/24 15:02:38 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
//add cwdr etc. to global variable for the aesthetics. (Done and Done)
//FIX THE WILDCARDS IN MAKEFILE!!!!!!
//FIX THE AESTHETICS OF THE EXIT COMMAND (done)
//Refactor
//Add the other commands(done)
//Add the bonus
//Add the leaks to collector
//Check the norm
//Check the leaks
//Move the files to the right folders and change the makefile
// Echo Doesn't prints more than 2 words, i f-ed it up with removing ac, dear future me handle that plox.
// 																			^^ ^ ^^ don't worry kiddo, i gotcha ;) <3 
// init_env is not working properly, order is changing while on a new prompt thats called with system call check why
// system call fix the aesthetics, fixed the path for each computer, env order gets f-ed up when this works. 
//ADD PATH CONTROL TO EXECUTOR <---- DONE BABYBOY, LOVE YA */

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
 	else if (pipe_exists(line) > 0)
		init_pipe(linefornow[0], linefornow);
	else if (if_execexist(linefornow[0]) == 1)
		execute(linefornow[0], linefornow);
	else if (linefornow[0] == NULL)
		return ;
	else
		printf("%sCommand not found\n", g_shell.cwdr);
}

void	open_terminal(char *av)//change it to execve
{
	if (ft_strncmp(av, "./minishell", 11) == 0)
	{
		system("open -a iTerm ./minishell");
		system("clear");
		exit (0);
	}
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
	system("clear");
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
