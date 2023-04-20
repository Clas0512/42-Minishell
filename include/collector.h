#ifndef COLLECTOR_H
# define COLLECTOR_H

#include <stdlib.h>
#include "minishell.h"

typedef struct s_collection
{
	void *address;
	struct s_collection *next;
}	t_collection;

typedef struct s_collector
{
	t_collection *head;
	t_collection *tail;
}	t_collector;

void init_collector(t_collector *collector);
t_collection *create_collection(void *address);
void add_collection(t_collector *collector, t_collection *new);

#endif