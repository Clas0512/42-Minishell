/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:24 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/21 00:16:12 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env()
{
	int	i;

	i = 0;
	while (shell.environments[i])
	{
		printf("%s\n", shell.environments[i]);
		i++;
	}
}

char *get_env(char *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = ft_strlen(env);
	tmp = NULL;
	while (shell.environments[i])
	{
		if (ft_strncmp(shell.environments[i], env, ft_strlen(env)) == 0)
		{
			if (ft_strncmp(tmp, "HOME=", 5) == 0)
			{
				tmp = ft_substr(shell.environments[i], j, ft_strlen(shell.environments[i]) - j);
				return (tmp);
			}
			i = 0;
			while (tmp[i] != '\0' && tmp[i + j] != '\0')
			{
				tmp[i] = tmp[i + j];
				i++;
			}
			
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

void	set_env(char *env, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (shell.environments[i])
	{
		if (ft_strncmp(shell.environments[i], env, ft_strlen(env)) == 0)
		{
			tmp = ft_strjoin(env, str);
			free(shell.environments[i]);
			shell.environments[i] = tmp;
			return ;
		}
		i++;
	}
}

void	init_env(void)
{
	int		i;
	char	*env;
	extern char **environ;

	i = 0;
	while (environ[i])
		i++;
	shell.environments = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		env = ft_strdup(environ[i]);
		shell.environments[i] = env;
		i++;
	}
	shell.environments[i] = NULL;
}
