/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:08:27 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/26 21:09:19 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(void)
{
	int			i;
	char		*env;
	extern char	**environ;

	i = 0;
	while (environ[i])
		i++;
	g_shell.environments = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		env = ft_strdup(environ[i]);
		g_shell.environments[i] = env;
		i++;
	}
	g_shell.environments[i] = NULL;
}
