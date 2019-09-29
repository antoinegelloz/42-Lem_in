/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:01:34 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/29 10:30:00 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	is_queue_full(t_bfs *bfs)
{
	return (bfs->queue_size == bfs->queue_capacity);
}

int8_t	is_queue_empty(t_bfs *bfs)
{
	return (bfs->queue_size == 0);
}

int8_t	enqueue(t_bfs *bfs, size_t index)
{
	if (is_queue_full(bfs) == TRUE)
		return (FAILURE);
	bfs->queue_rear = bfs->queue_rear + 1;
	bfs->queue[bfs->queue_rear] = index;
	bfs->queue_size = bfs->queue_size + 1;
	//printf("node %zd enqueued\n", index);
	return (SUCCESS);
}

int8_t	dequeue(t_bfs *bfs)
{
	size_t	index;

	if (is_queue_empty(bfs) == TRUE)
		return (FAILURE);
	index = bfs->queue[bfs->queue_front];
	bfs->queue_front = bfs->queue_front + 1;
	bfs->queue_size = bfs->queue_size - 1;
	//printf("node %zd dequeued\n", index);
	return (SUCCESS);
}

t_bfs	*create_queue(t_graph *graph)
{
	t_bfs	*bfs;
	size_t	i;

	bfs = (t_bfs *)malloc(sizeof(t_bfs));
	bfs->queue_capacity = graph->size;
	bfs->queue_front = 0;
	bfs->queue_size = 0;
	bfs->queue_rear = 0;
	bfs->queue = (ssize_t *)malloc(bfs->queue_capacity * sizeof(ssize_t));
	bfs->prev = (ssize_t *)malloc(bfs->queue_capacity * sizeof(ssize_t));
	i = 0;
	while (i < bfs->queue_capacity)
	{
		if (graph->nodes[i].source == TRUE)
		{
			bfs->queue[0] = i;
			bfs->queue_size = 1;
			graph->nodes[i].bfs_marked = TRUE;
			bfs->prev[i] = -1;
		}
		else
		{
			bfs->queue[i] = -1;
			bfs->prev[i] = -1;
		}
		i++;
	}
	bfs->best_path = NULL;
	return (bfs);
}
