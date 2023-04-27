/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:20 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 09:10:53 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	newline_solution(void)
{
	if (g_shell.echo_n == 0)
		printf("\n");
	g_shell.echo_n = 0;
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
	envtmp = g_shell.environments;
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

int	echo_n_control(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (i == 2 && av[0] == '-' && av[1] == 'n')
	{
		g_shell.echo_n = 1;
		return (1);
	}
	else
		g_shell.echo_n = 0;
	return (0);
}

int	echo_control(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && env_checker(arg) == 1)
			return (1);
		else if (arg[0] == '$' && arg[1] == '\0')
		{
			printf("$");
			return (1);
		}
		else if (arg[i] == '$' && env_checker(arg) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	echo(int ac, char **av) // if input is """ it fail.
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
		i++;
	ac = i;
	i = 0;
	while (i++ <= ac && av[i])
	{
		j = 0;
		while (av[i] && av[i][j] != '\0')
		{
			if (echo_n_control(av[1]) == 1 && g_shell.echo_n == 1)
				break ;
			else if (echo_control(av[i]) == 1)
				break ;
			else
				printf("%c", av[i][j]);
			j++;
		}
		if ((av[i] && av[i][j] == '\0') && av[i + 1] != NULL)
			printf(" ");
	}
	newline_solution();
}
