#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "minishell.h"

typedef struct s_redir
{
	char	*filename;
	int		result;
	int		fd;
	int		i;
	int		status;
	pid_t	pid;
}	t_redir;

typedef struct s_redir2
{
	int			delimiter_found;
	char		*line;
	char		*tmp_filename;
	int			tmp_fd;
	pid_t		pid;
	int			status;
}	t_redir2;

#endif