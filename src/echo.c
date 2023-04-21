/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:20 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/21 00:56:25 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Printing entra $ in echo fix that later

void	check_newline(int n)
{
	if (n == 0)
		printf("\n");
}

int	env_checker(char *envname)
{
	int		i;
	int		j;
	char	**envtmp;

	i = 0;
	j = ft_strlen(envname);
	if (envname[0] == '$' && ft_isalnum(envname[1]) != 0)
		envname++;
	envtmp = shell.environments;
	while (envtmp[i] != NULL)
	{
		if (ft_strncmp(envtmp[i], envname, ft_strlen(envname)) == 0)
		{
			while (envtmp[i][j] != '\0')
			{
				printf("%c", envtmp[i][j]);
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	echo(char **av)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (i++)
	{
		j = 0;
		while (av[i] && av[i][j] != '\0')
		{
			if (av[1][0] == '-' && av[1][1] == 'n')
			{
				n = 1;
				break ;
			}
			else if ((av[i][j] == '$' && env_checker(av[i]) == 1))
				break ;
			else if (av[i][0] == '$' && av[i][1] == '\0')
				printf("$");
			else if (av[i][j] == '$' && env_checker(av[i]) == 0)
			{
				printf("\n");
				break ;
			}
			else
				printf("%c", av[i][j]);
			j++;
		}
		if ((av[i] && av[i][j] == '\0') && av[i + 1] != NULL)
			printf(" ");
	}
	check_newline(n);
}
