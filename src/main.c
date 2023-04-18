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
t_shell shell;

int	main(int ac, char *av[], char *env[])
{
	char	*line;
	char	**linefornow;
	char	*cwdr;
	if (ft_strncmp(av[0], "./minishell", 11) == 0)
	{
		system("open -a iterm ./minishell"); //fix the aesthetics, fixed the path for each computer
		exit(0);
	}
	(void)ac;
	(void)av;
	(void)env;
	init_env(); //order is changing in seperate terminal, check why
	init_collector(&shell.collector);
	init_commander(&shell.commander);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(EOF, handle_signal);
	while (true)
	{
		cwdr = ft_strjoin(getcwd(NULL, 0), " | minishell> ");
		line = readline(cwdr);
		if (line == NULL)
		{
			printf("%s exit", cwdr);
			exit(0);
		}
		linefornow = ft_split(line, ' ');
		add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit_minishell(linefornow);//works for now but should fix the aesthetics
		else if (ft_strncmp(line, "echo", 4) == 0 || ft_strncmp(line, "ECHO", 4) == 0)
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
			change_dir(linefornow);
		else
			printf("%s: command not found\n", line);
		free(line);
		free(linefornow);
		free(cwdr);
	}
	return (0);
}
