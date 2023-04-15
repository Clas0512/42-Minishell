#include "minishell.h"

void	checknewline(int n)
{
	if (n == 0)
		printf("\n");
}

int	white_checker(char c, char d)
{
	if (c == '\\' && d != '\0')
	{
		if (d == 'n')
			printf("\n");
		else if (d == 't')
			printf("\t");
		else if (d == 'v')
			printf("\v");
		else if (d == 'b')
			printf("\b");
		else if (d == 'r')
			printf("\r");
		else if (d == 'f')
			printf("\f");
		else if (d == 'a')
			printf("\a");
		return (1);
	}
	else
		return (0);
}

int	env_checker(char *envname)
{
	int		i;
	char 	**envtmp;

	i = 0;
	envtmp = shell.environments;
	while (envtmp[i] != NULL)
	{
		if (ft_strncmp(envtmp[i], envname, ft_strlen(envname)) == 0)
		{
			printf("%s", envtmp[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	echo(int ac, char **av)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (i++ < ac)
	{
		j = 0;
		while (av[i] && av[i][j] != '\0')
		{
			if (av[1][0] == '-' && av[1][1] == 'n')
			{
				n = 1;
				break ;
			}
			else if ((av[i][j] == '$' && av[i][j + 1] == '\0') ||
			(av[i][j] == '$' && env_checker(av[i]) == 0) ||
			(av[i][j] == '$' && white_checker(av[i][j], av[i][j + 1]) == 0))
				printf("$");
			else if (white_checker(av[i][j], av[i][j + 1]) == 0)
				printf("%c", av[i][j]);
			j++;
		}
		if ((av[i] && av[i][j] == '\0') && av[i + 1] != NULL)
			printf(" ");
	}
	checknewline(n);
}
