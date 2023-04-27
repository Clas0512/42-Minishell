/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:36:12 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 13:12:39 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_redir(char **linefornow)
{
	int	i;

	i = 0;
	while (linefornow[i] != NULL)
		i++;
	if (i == 1 && (redirection_exists(linefornow[0]) == 0 || pipe_exists(linefornow[0]) == 0))
	{
		g_shell.exit_status = 258;
		return (0);
	}
	return (1);
}

int	check_syntax_builtin3(char **linefornow)
{
	if (ft_strncmp(linefornow[0], "env", 3) == 0)
	{
		print_env();
		return (0);
	}
	else if (ft_strncmp(linefornow[0], "unset", 5) == 0)
	{
		unset_env(linefornow);
		return (0);
	}
	else if (ft_strncmp(linefornow[0], "export", 6) == 0)
	{
		export_env(linefornow);
		return (0);
	}
	else if (ft_strncmp(linefornow[0], "cd", 3) == 0)
	{
		change_directory(linefornow);
		return (0);
	}
	return (1);
}

int	check_syntax_builtin2(char **linefornow)
{
	if (ft_strncmp(linefornow[0], "exit", 4) == 0)
	{
		exit_minishell(linefornow);
		return (0);
	}
	else if (ft_strncmp(linefornow[0], "echo", 4) == 0)
	{
		echo(0, linefornow);
		return (0);
	}
	else if (ft_strncmp(linefornow[0], "pwd", 3) == 0)
	{
		pwd();
		return (0);
	}
	else if (check_syntax_builtin3(linefornow) == 0)
		return (0);
	return (1);
}

int	check_syntax_builtin(char **linefornow)
{
	if (check_syntax_builtin2(linefornow) == 0)
	{
		g_shell.exit_status = 0;
		return (0);
	}
	else if (check_syntax_builtin3(linefornow) == 0)
	{
		g_shell.exit_status = 0;
		return (0);
	}
	return (1);
}

int	check_exit_status(char **linefornow)
{
	if (ft_strncmp(linefornow[0], "echo", 4) == 0)
	{
		if (ft_strncmp(linefornow[1], "$?", 2) == 0)
		{
			printf("%d\n", g_shell.exit_status);
			g_shell.exit_status = 0;
			return (0);
		}
	}
	else if (ft_strncmp(linefornow[0], "$?", 2) == 0)
	{
		printf("%s Command not found : %d\n",g_shell.cwdr, g_shell.exit_status);
		g_shell.exit_status = 127;
		return (0);
	}
	return (1);
}
