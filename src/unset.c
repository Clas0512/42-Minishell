/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:34:02 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/22 04:07:28 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env(char **unsettling)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(unsettling[1]);
	while (g_shell.environments[i])
	{
		if (ft_strncmp(g_shell.environments[i], unsettling[1], j) == 0)
		{
			while (g_shell.environments[i])
			{
				g_shell.environments[i] = g_shell.environments[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}
