/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:34:02 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/19 23:29:32 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unsetEnv(char **unsettling)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(unsettling[1]);
	while (shell.environments[i])
	{
		if (ft_strncmp(shell.environments[i], unsettling[1], j) == 0)
		{
			while (shell.environments[i])
			{
				shell.environments[i] = shell.environments[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}
