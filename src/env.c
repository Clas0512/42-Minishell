/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:24 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/26 21:08:17 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(void)
{
	int	i;

	i = 0;
	while (g_shell.environments[i])
	{
		printf("%s\n", g_shell.environments[i]);
		i++;
	}
}

char	*tmp_filler(char *tmp, int j, int i)
{
	int	k;

	k = ft_strlen(g_shell.environments[i]) - j;
	if (ft_strncmp(tmp, "HOME=", 5) == 0)
	{
		tmp = ft_substr(g_shell.environments[i], j, k);
		return (tmp);
	}
	i = 0;
	while (tmp[i] != '\0' && tmp[i + j] != '\0')
	{
		tmp[i] = tmp[i + j];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*get_env(char *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = ft_strlen(env);
	tmp = NULL;
	while (g_shell.environments[i])
	{
		if (ft_strncmp(g_shell.environments[i], env, j) == 0)
		{
			tmp = tmp_filler(tmp, j, i);
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
	while (g_shell.environments[i])
	{
		if (ft_strncmp(g_shell.environments[i], env, ft_strlen(env)) == 0)
		{
			tmp = ft_strjoin(env, str);
			free(g_shell.environments[i]);
			g_shell.environments[i] = tmp;
			return ;
		}
		i++;
	}
}

char	*get_env_variable(char *var_name)
{
	int		i;
	char	*var;
	char	*temp;

	i = 0;
	while (g_shell.environments[i])
	{
		temp = g_shell.environments[i];
		if (ft_strncmp(temp, var_name, ft_strlen(var_name)) == 0)
		{
			var = ft_substr(temp, ft_strlen(var_name) + 1, ft_strlen(temp));
			return (var);
		}
		i++;
	}
	return (NULL);
}
