/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:40 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/21 20:13:10 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* //add cwdr etc. to global variable for the aesthetics.
//FIX THE WILDCARDS IN MAKEFILE!!!!!!
//FIX THE AESTHETICS OF THE EXIT COMMAND
//Refactor
//Add the other commands
//Add the bonus
//Add the leaks to collector
//Check the norm
//Check the leaks
//Move the files to the right folders and change the makefile
// Echo Doesn't prints more than 2 words, i f-ed it up with removing ac, dear future me handle that plox
// exit works for now but should fix the aesthetics
// init_env is not working properly, order is changing while on a new prompt thats called with system call check why
// system call fix the aesthetics, fixed the path for each computer, env order gets f-ed up when this works. */
t_shell	shell;

void	read_the_line(char *line, char **linefornow)
{
	if (ft_strncmp(linefornow[0], "exit", 4) == 0)
		exit_minishell(linefornow);
	else if (ft_strncmp(linefornow[0], "echo", 4) == 0
		|| ft_strncmp(linefornow[0], "ECHO", 4) == 0)
		echo(linefornow);
	else if (ft_strncmp(linefornow[0], "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(linefornow[0], "env", 3) == 0 || ft_strncmp(linefornow[0], "ENV", 3) == 0)
		print_env();
	else if (ft_strncmp(linefornow[0], "unset", 5) == 0)
		unset_env(linefornow);
	else if (ft_strncmp(linefornow[0], "export", 6) == 0)
		export_env(linefornow);
	else if (ft_strncmp(linefornow[0], "cd", 2) == 0)
		change_directory(linefornow);
	else
		printf("%s: command not found\n", line);
}

void	open_terminal(char *av)
{
	if (ft_strncmp(av, "./minishell", 11) == 0)
	{
		system("open -a iTerm ./minishell");
		exit (0);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**linefornow;

	//open_terminal(av[0]);
	(void)ac;
	(void)av;
	(void)env;
	init_env();
	init_collector(&shell.collector);
	init_commander(&shell.commander);
	init_signal();
	while (true)
	{
		shell.cwdr = ft_strjoin(getcwd(NULL, 0), " | minishell> ");
		line = readline(shell.cwdr);
		linefornow = lexer(line);
		printf("\n\n -*------ %p -------*-\n\n", linefornow);
		if (line == NULL)
		{
			printf("%s exit", shell.cwdr);
			exit(0);
		}
		// linefornow = ft_split(line, ' ');
		add_history(line);
		read_the_line(line, linefornow);
		free(line);
		free(linefornow);
		free(shell.cwdr);
	}
	return (0);
}
