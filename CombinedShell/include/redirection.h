/* #ifndef REDIRECTION_H
# define REDIRECTION_H

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_redirection
{
	int	fd;
	char *name;
	struct s_redirection *next;
}	t_redirection;

typedef struct s_director
{
	t_redirection *append_head;
	t_redirection *heredoc_head;
	t_redirection *infile_head;
	t_redirection *outfile_head;
	t_redirection *append_tail;
	t_redirection *heredoc_tail;
	t_redirection *infile_tail;
	t_redirection *outfile_tail;
}	t_director;

t_redirection *create_redirection(char *name, int flags);
void init_director(t_director *director);
void add_redirection(t_redirection **head, t_redirection **tail, t_redirection *new);

#endif */