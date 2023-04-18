#include "minishell.h"

//EOF signal gives seg-fault, should fix it. 
//It was working before but now its not and idk why lol, such a classic. 
//I swear i didn't even touched it ;-; it might be about system call.
//CHECK THIS WTF --->I think i fixed it, it was about the EOF signal, i changed it to 0 and it works now.
//add cwdr etc. to global variable for the aesthetics.
t_shell shell;

int	main(int ac, char *av[], char *env[])
{
	char	*line;
	char	*cwdr;
	char	**linefornow;
	if (ft_strncmp(av[0], "./minishell", 11) == 0)
	{
		system("open -a Terminal ./minishell"); //fix the aesthetics, fix the path for each computer
		exit(0);
	}
	(void)ac;
	(void)av;
	(void)env;
	//environ changes the order idk why but gotta fix that
	init_env();
	init_collector(&shell.collector);
	init_commander(&shell.commander);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(EOF, handle_signal);
	cwdr = ft_strjoin(get_pwd(), " | minishell> ");
	while (true)
	{
		line = readline(cwdr);
		linefornow = ft_split(line, ' ');
		add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit_minishell(linefornow);//works for now but should fix the aesthetics
		else if (ft_strncmp(line, "echo", 4) == 0 || ft_strncmp(line, "ECHO", 4) == 0)
			echo(ac, linefornow); //works for now
		else if (ft_strncmp(line, "pwd", 3) == 0)
			pwd();//works for now
		else if (ft_strncmp(line, "env", 3) == 0 || ft_strncmp(line, "ENV", 3) == 0)
			print_env();//works for now
 		else if (ft_strncmp(line, "unset", 5) == 0)
			unset_env(linefornow);//works for now
		else if (ft_strncmp(line, "export", 6) == 0)
			export_env(linefornow);//works for now
 		else if (ft_strncmp(line, "cd", 2) == 0)
			change_dir(linefornow); //Gonna fix this later//fixed cd .. but the rest is not working yet
		else
			printf("%s: command not found\n", line);
		free(line);
		free(linefornow);
	}
	return (0);
}
