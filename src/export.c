/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:31 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/21 00:07:21 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// change free's with collector cleaner
//add to collector
//just use a temp ** and change it to shell.environments

//export command for shell with no options
void	export_env(char **newenvname)
{
	t_shell	tempenv;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (shell.environments[i])
		i++;
	tempenv.environments = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shell.environments[i])
	{
		tempenv.environments[i] = ft_strdup(shell.environments[i]);
		i++;
	}
	tempenv.environments[i] = ft_strdup(newenvname[1]);
	tempenv.environments[i + 1] = NULL;
	while (shell.environments[++j])
		free(shell.environments[j]);
	free(shell.environments[j]);
	shell.environments = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tempenv.environments[i])
	{
		shell.environments[i] = ft_strdup(tempenv.environments[i]);
		i++;
	}
	shell.environments[i] = NULL;
	i = -1;
	while (tempenv.environments[++i])
		free(tempenv.environments[i]);
	free(tempenv.environments);
}
