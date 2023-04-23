/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:46 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/22 04:37:54 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell.h"

t_shell shell;

t_redirection *create_redirection(char *name, int flags)
{
	t_redirection *new;
	t_collection collection;

	new = malloc(sizeof(t_redirection));
	new->name = name;
	new->fd = open(name, flags);
	new->next = NULL;
	collection = create_collection(new);
	add_collection(&g_shell.collector, collection);
	return (new);
}

void init_director(t_director *director)
{
	director->append_head = NULL;
	director->append_tail = NULL;
	director->heredoc_head = NULL;
	director->heredoc_tail = NULL;
	director->infile_head =NULL;
	director->infile_tail = NULL;
	director->outfile_head = NULL;
	director->outfile_tail = NULL; 
}

void add_redirection(t_redirection **head, t_redirection **tail, t_redirection *new)
{
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = (*tail)->next;
	}
} */