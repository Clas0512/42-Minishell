/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:14 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/28 00:38:21 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*initialize collector's variables*/
void init_collector(t_collector *collector)
{
	collector->head = NULL;
	collector->tail = NULL;
}

/*create a collection node variable*/
void	*create_collection(void *address)
{
	t_collection	*new;

	new = malloc(sizeof(t_collection));
	new->next = NULL;
	new->address = address;
	add_collection(new);
}

/*add collection node to collector.*/
void	add_collection(t_collection *new)
{
	if (g_shell.collector.head == NULL)
	{
		g_shell.collector.head = new;
		g_shell.collector.tail = new;
	}
	else
	{
		g_shell.collector.tail->next = new;
		g_shell.collector.tail = g_shell.collector.tail->next;
	}
}
