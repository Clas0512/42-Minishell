#ifndef COMMAND_H
# define COMMAND_H

#include "string.h"
#include "minishell.h"

typedef struct s_command
{
	struct s_command *next;
	struct s_command *prev;
	int pipe_fds[2];
	//t_director director;
	//t_string *entire_command;
	//t_string command_name;
}	t_command;

typedef struct s_commander
{
	t_command	*head;
	t_command	*tail;
}	t_commander;

void initCommander(t_commander *commander);
//t_command *create_command(t_commander *commander, t_string *lexed);
void add_command(t_commander *commander, t_command *new);

#endif
