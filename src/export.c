/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:31 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/22 04:07:28 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// change free's with collector cleaner
//add to collector
//just use a temp ** and change it to g_shell.environments

//export command for shell with no options
void	export_env(char **newenvname)
{
	t_shell	tempenv;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (g_shell.environments[i])
		i++;
	tempenv.environments = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (g_shell.environments[i])
	{
		tempenv.environments[i] = ft_strdup(g_shell.environments[i]);
		i++;
	}
	tempenv.environments[i] = ft_strdup(newenvname[1]);
	tempenv.environments[i + 1] = NULL;
	while (g_shell.environments[++j])
		free(g_shell.environments[j]);
	free(g_shell.environments[j]);
	g_shell.environments = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tempenv.environments[i])
	{
		g_shell.environments[i] = ft_strdup(tempenv.environments[i]);
		i++;
	}
	g_shell.environments[i] = NULL;
	i = -1;
	while (tempenv.environments[++i])
		free(tempenv.environments[i]);
	free(tempenv.environments);
}
