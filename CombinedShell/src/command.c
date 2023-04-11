#include "minishell.h"

void init_commander(t_commander *commander)
{
	commander->head = NULL;
	commander->tail = NULL;
}

t_command *create_command(t_commander *commander)
{
	t_command *new;
	t_collection *collection;

	new = malloc(sizeof(t_command));
	new->next = NULL;
	if (commander->tail == NULL)
		new->prev = NULL;
	else
		new->prev = commander->tail;
	collection = create_collection(new);
	add_collection(&shell.collector, collection);
	return (new);
}

void add_command(t_commander *commander, t_command *new)
{
	if (commander->head == NULL)
	{
		commander->head = new;
		commander->tail = new;
	}
	else
	{
		commander->tail->next = new;
		commander->tail = commander->tail->next;
	}
}
