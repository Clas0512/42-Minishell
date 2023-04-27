/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:08:27 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 19:06:11 by aerbosna         ###   ########.fr       */
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

void	pipe_execute_init(int mod)
{
	if (mod == 1)
		g_shell.pipe.pipes = malloc(sizeof(int) * g_shell.pipe.num_pipes * 2);
	else
	{
		g_shell.pipe.num_pipes = 0;
		g_shell.pipe.pipeargs_idx = 0;
		g_shell.pipe.args = NULL;
		g_shell.pipe.start = 0;
		g_shell.pipe.end = 0;
		g_shell.pipe.pipe_idx = 0;
		g_shell.pipe.i = 0;
	}
}

void	redir_init(void)
{
	g_shell.redir.i = -1;
	g_shell.redir.status = 0;
	g_shell.redir.pid = 0;
	g_shell.redir.fd = 0;
	g_shell.redir.result = 0;
	g_shell.redir.filename = NULL;
}