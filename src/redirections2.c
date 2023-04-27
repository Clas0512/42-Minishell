/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:47:16 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/27 20:04:26 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append(char **args)
{
	int	fd;
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], ">>", 1) == 0)
			break ;
		i++;
	}
	if (ft_strncmp(args[i], ">>", 2) == 0)
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	if (dup2(fd, STDOUT_FILENO) == -1)
		return ;
	if (close(fd) == -1)
		return ;
	execute(args[0], args);
	exit(EXIT_FAILURE);
}

void	outfile_childe(char **args)
{
	int		i;
	char	*output;
	int		fd;

	i = 0;
	output = NULL;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], ">", 1) == 0)
		{
			output = args[i + 1];
			args[i] = NULL;
			break ;
		}
		i++;
	}
	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	execute(args[0], args);
	exit(EXIT_FAILURE);
}

void	outfile(char **args)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		outfile_childe(args);
	else
		waitpid(pid, &status, 0);
}
