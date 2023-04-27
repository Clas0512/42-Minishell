/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 05:01:52 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/26 17:23:36 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//FIX THE INFILE OUTCOME

//checks to see if the command has a redirection
int	redirection_exists(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<' )
			return (0);
		i++;
	}
	return (1);
}

//checks to see if the command is infile, outfile, append or heredoc
void	redirection_redirector(char **linefornow)
{
	int	i;
	char	*cmd[] = {"grep", "example", NULL};

	i = 0;
	while (linefornow[i])
	{
		if (ft_strncmp(linefornow[i], ">>", 2) == 0)
		{
			append(linefornow);
			break ;
		}
		else if (ft_strncmp(linefornow[i], "<<", 2) == 0)
		{
			heredoc(cmd, "EFF");
			break ;
		}
		else if (ft_strncmp(linefornow[i], ">", 1) == 0)
			outfile(linefornow);
		else if (ft_strncmp(linefornow[i], "<", 1) == 0)
			infile(linefornow);
		i++;
	}
}

void	infile(char **args)
{
	char	*filename;
	int		result;
	int		fd;
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	filename = NULL;
	status = 0;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "<", 1) == 0)
		{
			filename = args[i + 1];
			args[i] = NULL;
			break ;
		}
		i++;
	}
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			exit(EXIT_FAILURE);
		result = dup2(fd, STDIN_FILENO);
		if (result < 0)
			exit(EXIT_FAILURE);
		execute(args[0], args);
	}
	else
		waitpid(pid, &status, 0);
}

void	outfile(char **args) 
{
	char	*output;
	int		status;
	int		fd;
	int		i;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
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
	else
		waitpid(pid, &status, 0);
}

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
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (dup2(fd, STDOUT_FILENO) == -1)
		return ;
	if (close(fd) == -1)
		return ;
	execute(args[0], args);
	exit(EXIT_FAILURE);
}

void	heredoc(char **args, char *delimiter)
{
	int			delimiter_found;
	char		*line;
	const char	tmp_filename[] = "/tmp/heredoc.tmp";
	int			tmp_fd;
	pid_t		pid;
	int			status;
	int			input_fd;

	tmp_fd = open(tmp_filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	delimiter_found = 1;
	if (delimiter_found == 1)
		delimiter_found = 0;
	printf("> ");
	while ((line = readline(NULL)) != NULL)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			delimiter_found = 1;
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
		printf("> ");
	}
	close(tmp_fd);
	pid = fork();
	if (pid == 0)
	{
		input_fd = open(tmp_filename, O_RDONLY);
		if (input_fd == -1)
			exit(1);
		if (dup2(input_fd, STDIN_FILENO) == -1)
			exit(1);
		close(input_fd);
		execute(args[0], args);
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
	unlink(tmp_filename);
}
