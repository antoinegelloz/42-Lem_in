/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/25 18:43:36 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	find_index(int data, int *array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		if (array[i] == data)
			break ;
		i++;
	}
	return (i);
}

int			get_queue(t_graph *graph)
{
	int		i;
	t_queue *queue;
	t_edge	*lst;

	queue = create_queue(graph->size);
	i = 0;
	while (graph->array[i])
	{
		if (graph->array[i]->source == TRUE)
		{
			queue[0] = graph->array[i]->index;
			break;
		}
		i++;
	}

	while (isEmpty(queue) == FALSE)
	{
		graph->array[i]->bfs_marked = TRUE;
		dequeue(queue);
		lst = graph->array[i]->head;
		while (lst->next)
		{
			lst = lst->next;
			enqueue(queue, lst->dest);
		}
		i = find_index(queue[queue->front], graph->array);
	}
}
