/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:28 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/22 23:36:15 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_fixer(char **exitargs)
{
	printf("%sexit: %s numeric argument required\n", g_shell.cwdr, exitargs[1]);
	printf("exit\n");
	exit(0);
}

void	exit_minishell(char **exitargs)
{
	int	i;

	i = 0;
	if (exitargs[1] != NULL)
	{
		if (ft_isdigit(exitargs[1][i]) == 0)
			norm_fixer(exitargs);
		else if (ft_isdigit(exitargs[1][i]) >= '0'
		&& ft_isdigit(exitargs[1][i]) <= '9')
		{
			printf("%sexit: %s\n", g_shell.cwdr, exitargs[1]);
			printf("exit\n");
			exit(ft_atoi(exitargs[1]));
		}
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
