/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:33:14 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/19 23:23:04 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*initialize collector's variables*/
void initCollector(t_collector *collector)
{
	collector->head = NULL;
	collector->tail = NULL;
}

/*create a collection node variable*/
t_collection *create_collection(void *address)
{
	t_collection *new;

	new = malloc(sizeof(t_collection));
	new->next = NULL;
	new->address = address;
	return (new);
}

/*add collection node to collector.*/
void add_collection(t_collector *collector, t_collection *new)
{
	if (collector->head == NULL)
	{
		collector->head = new;
		collector->tail = new;
	}
	else
	{
		collector->tail->next = new;
		collector->tail = collector->tail->next;
	}
}