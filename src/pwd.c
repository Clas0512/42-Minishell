/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:43 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/28 00:48:17 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	int		i;
	int		j;
	char	**envtmp;

	i = 0;
	j = 0;
	envtmp = g_shell.environments;
	while (envtmp[i] != NULL)
	{
		if (ft_strncmp(envtmp[i], "PWD=", 4) == 0)
		{
			while (envtmp[i][j + 4] != '\0')
			{
				printf("%c", envtmp[i][j + 4]);
				j++;
			}
			printf("\n");
			return ;
		}
		i++;
	}
}

char	*get_pwd(void)
{
	int		i;
	size_t	j;
	char	**envtmp;
	char	*pwd;

	i = 0;
	j = 0;
	envtmp = g_shell.environments;
	while (envtmp[i] != NULL)
	{
		if (ft_strncmp(envtmp[i], "PWD=", 4) == 0)
		{
			pwd = malloc(sizeof(char) * (ft_strlen(envtmp[i]) - 3));
			create_collection(pwd);
			while (j < ft_strlen(envtmp[i]) - 4)
			{
				pwd[j] = envtmp[i][j + 4];
				j++;
			}
			pwd[j] = '\0';
			return (pwd);
		}
		i++;
	}
	return (NULL);
}
