/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:40 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/20 22:21:05 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//add cwdr etc. to global variable for the aesthetics.
//FIX THE WILDCARDS IN MAKEFILE!!!!!!
//FIX THE AESTHETICS OF THE EXIT COMMAND
//Refactor
//Add the other commands
//Add the bonus
//Add the leaks to collector
//Check the norm
//Check the leaks
//Move the files to the right folders and change the makefile
t_shell	shell;

void	readTheLine(char *line, char **linefornow)
{
	if (ft_strncmp(line, "exit", 4) == 0)
		exitMinishell(linefornow);//works for now but should fix the aesthetics
	else if (ft_strncmp(line, "echo", 4) == 0
		|| ft_strncmp(line, "ECHO", 4) == 0)
		echo(linefornow);//Doesn't prints more than 2 words, i f-ed it up with removing ac, dear future me handle that plox
	else if (ft_strncmp(line, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(line, "env", 3) == 0 || ft_strncmp(line, "ENV", 3) == 0)
		printEnv();
	else if (ft_strncmp(line, "unset", 5) == 0)
		unsetEnv(linefornow);
	else if (ft_strncmp(line, "export", 6) == 0)
		exportEnv(linefornow);
	else if (ft_strncmp(line, "cd", 2) == 0)
		changeDirectory(linefornow);
	else
		printf("%s: command not found\n", line);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**linefornow;
	
	if (ft_strncmp(av[0], "./minishell", 11) == 0)
	{
		system("open -a iterm ./minishell"); //fix the aesthetics, fixed the path for each computer// env order gets f-ed up when this works. 
		exit(0);
	}
	(void)ac;
	(void)av;
	(void)env;
	initEnv(); //order is changing in seperate terminal, check why
	initCollector(&shell.collector);
	initCommander(&shell.commander);
	signal(SIGINT, handleSignal);
	signal(SIGQUIT, handleSignal);
	signal(EOF, handleSignal);
	while (true)
	{
		shell.cwdr = ft_strjoin(getcwd(NULL, 0), " | minishell> ");
		line = readline(shell.cwdr);
		if (line == NULL)
		{
			printf("%s exit", shell.cwdr);
			exit(0);
		}
		linefornow = ft_split(line, ' ');
		add_history(line);
		readTheLine(line, linefornow);
		free(line);
		free(linefornow);
		free(shell.cwdr);
	}
	return (0);
}
