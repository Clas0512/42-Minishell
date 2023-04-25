/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:10 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/22 03:41:14 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_one_up(char **cdargs)
{
	if (chdir(cdargs[1]) == -1)
		printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
	else
		change_new_pwd();
}

void	go_back(void)
{
	char	*tmp;

	tmp = get_env("OLDPWD=");
	if (chdir(tmp) == -1)
		printf("minishell: cd: %s: No such file or directory\n", tmp);
	else
		change_new_pwd();
	free(tmp);
}

void	go_home(void)
{
	char	*tmp;

	tmp = get_env("HOME=");
	if (chdir(tmp) == -1)
		printf("minishell: cd: %s: No such file or directory\n", tmp);
	else
		change_new_pwd();
	free(tmp);
}

void	change_new_pwd(void)
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

void	change_directory(char **cdargs)
{
	if (ft_strncmp(cdargs[0], "cd", 2) == 0)
	{
		if (cdargs[1] == NULL || (cdargs[1][0] == '~' && cdargs[1][1] == '\0'))
			go_home();
		else if (cdargs[2] != NULL)
			printf("minishell: cd: too many arguments\n");
		else if (cdargs[1][0] == '-')
			go_back();
		else if (cdargs[1][0] == '.' && cdargs[1][1] == '.')
			go_one_up(cdargs);
		else if (chdir(cdargs[1]) == -1)
			printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
		else
			change_new_pwd();
	}
}
