/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:10 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/19 23:29:52 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	changeNewPwd()
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	tmp = getEnv("PWD=");
	tmp2 = getcwd(NULL, 0);
	setEnv("PWD=", tmp2);
	setEnv("OLDPWD=", tmp);
	free(tmp);
	free(tmp2);
}

void	changeDirectory(char **cdargs)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(cdargs[0], "cd", 2) == 0)
	{
		if (cdargs[1] == NULL)
		{
			tmp = getEnv("HOME=");
			if (chdir(tmp) == -1)
				printf("minishell: cd: %s: No such file or directory\n", tmp);
			else
				changeNewPwd();
			free(tmp);
		}
		else if (cdargs[2] != NULL)
			printf("minishell: cd: too many arguments\n");
		else if (cdargs[1][0] == '~')
		{
			tmp = getEnv("HOME=");
			if (chdir(tmp) == -1)
				printf("minishell: cd: %s: No such file or directory\n", tmp);
			else
				changeNewPwd();
			free(tmp);
		}
		else if (cdargs[1][0] == '-')
		{
			tmp = getEnv("OLDPWD=");
			if (chdir(tmp) == -1)
				printf("minishell: cd: %s: No such file or directory\n", tmp);
			else
				changeNewPwd();
			free(tmp);
		}
		else if (cdargs[1][0] == '.' && cdargs[1][1] == '.')//works fine
		{
			if (chdir(cdargs[1]) == -1)
				printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
			else
				changeNewPwd();
			free(tmp);
		}
		else if (chdir(cdargs[1]) == -1)
			printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
		else
			changeNewPwd();
	}
}
