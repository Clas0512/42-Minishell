#include "minishell.h"

//exit the program
void	exit_minishell(char **exitargs)
{
	int	i;

	i = 0;
	if (exitargs[2])
	{
		if (ft_isdigit(exitargs[2][0]))
		{
			while (exitargs[2][i])
			{
				if (!ft_isdigit(exitargs[2][i]))
				{
					printf("exit : %s : numeric argument required\n", exitargs[2]);
				}
				i++;
			}
			exit(ft_atoi(exitargs[2]));
		}
		else
		{
			printf("exit : %s : numeric argument required\n", exitargs[2]);
			return ;
		}
	}
	exit(0);
}