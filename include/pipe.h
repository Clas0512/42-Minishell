#ifndef PIPE_H
# define PIPE_H

#include "minishell.h"

typedef struct s_pipe
{
	int		num_pipes;
	int		pipeargs_idx;
	int		pipe_idx;
	int		wstatus;
	int		start;
	int		end;
	int		i;
	char	**args;
	int		*pipes;
	pid_t	pid;
}	t_pipe;

#endif