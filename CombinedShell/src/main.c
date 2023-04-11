#include "minishell.h"

t_shell shell;

int	main(int ac, char *av[], char *env[])
{
	char	*line;
	(void)ac;
	(void)av;
	(void)env;
	init_collector(&shell.collector);
	init_commander(&shell.commander);
	init_env();
	//system("open -a Terminal /Users/Ventum/Desktop/CombinedShell/minishell");
	signal(SIGINT, handle_signal);
	while (true)
	{
		line = readline("minishell> ");
		if (ft_strncmp(line, "exit", 4) == 0)
			exit_minishell(&line);
		else if (ft_strncmp(line, "echo", 4) == 0)
			echo(ac, &line);
		else if (ft_strncmp(line, "cd", 2) == 0)
			cd(&line);
		else if (ft_strncmp(line, "pwd", 3) == 0)
			pwd();
		else if (ft_strncmp(line, "export", 6) == 0)
			export(&line);
		else if (ft_strncmp(line, "unset", 5) == 0)
			unset_env(line);
		else if (ft_strncmp(line, "env", 3) == 0)
			print_env();
		else
			printf("command not found\n");
		free(line);
	}
	return (0);
}

//learn readline, work on functions allowed, fix here, add a working history and a tree, learn what is commands what is not