#include "minishell.h"

int	echo_mid_checker(char *arg)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			while (j < i)
			{
				printf("%c", arg[j]);
				j++;
			}
			tmp = ft_strdup(arg + i);
			env_checker(tmp);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}
