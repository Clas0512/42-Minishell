/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:10 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/18 22:33:11 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	changenewpwd()
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	tmp = get_env("PWD=");
	tmp2 = getcwd(NULL, 0);
	set_env("PWD=", tmp2);
	set_env("OLDPWD=", tmp);
	free(tmp);
	free(tmp2);
}

void	change_dir(char **cdargs)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(cdargs[0], "cd", 2) == 0)
	{
		if (cdargs[1] == NULL)
		{
			tmp = get_env("HOME=");
			if (chdir(tmp) == -1)
				printf("minishell: cd: %s: No such file or directory\n", tmp);
			else
				changenewpwd();
			free(tmp);
		}
		else if (cdargs[2] != NULL)
			printf("minishell: cd: too many arguments\n");
		else if (cdargs[1][0] == '~')
		{
			tmp = get_env("HOME=");
			if (chdir(tmp) == -1)
				printf("minishell: cd: %s: No such file or directory\n", tmp);
			else
				changenewpwd();
			free(tmp);
		}
		else if (cdargs[1][0] == '-')
		{
			tmp = get_env("OLDPWD=");
			if (chdir(tmp) == -1)
				printf("minishell: cd: %s: No such file or directory\n", tmp);
			else
				changenewpwd();
			free(tmp);
		}
		else if (cdargs[1][0] == '.' && cdargs[1][1] == '.')//works fine
		{
			if (chdir(cdargs[1]) == -1)
				printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
			else
				changenewpwd();
			free(tmp);
		}
		else if (chdir(cdargs[1]) == -1)
			printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
		else
			changenewpwd();
	}
}
