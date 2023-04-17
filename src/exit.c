#include "minishell.h"

void	exit_minishell(char **exitargs)
{
	int	i;

	i = 0;
	if (exitargs[1] != NULL)
	{
		if (ft_isdigit(exitargs[1][i]) == 0)
		{
			printf("exit: %s numeric argument required\n", exitargs[1]);
			printf("exit\n");
			exit(0);
		}
		else if(ft_isdigit(exitargs[1][i]) >= '0' && ft_isdigit(exitargs[1][i]) <= '9')
		{
			printf("exit: %s\n", exitargs[1]);
			printf("exit\n");
			exit(ft_atoi(exitargs[1]));
		}
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
