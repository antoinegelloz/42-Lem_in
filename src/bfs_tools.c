/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:01:34 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/26 12:43:00 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t		change_capacity(t_graph *graph, t_list *u, t_list *v, int8_t order)
{
	t_edge	*neighbours;

	neighbours = graph->nodes[*(size_t *)u->content].head;
	while (neighbours->dest != *(size_t *)v->content)
		neighbours = neighbours->next;
	if (neighbours->dest == *(size_t *)v->content)
	{
		if (order == INCREASE)
			neighbours->capacity++;
		if (order == DECREASE)
			neighbours->capacity--;
	}
	return (SUCCESS);
}

int8_t			is_queue_empty(t_bfs *bfs)
{
	return (bfs->queue_size == 0);
}

int8_t			enqueue(size_t node, size_t neighbour, t_graph *graph, t_bfs *bfs)
{
	if (bfs->queue_size == bfs->queue_capacity)
		return (FAILURE);
	bfs->queue_rear = bfs->queue_rear + 1;
	bfs->queue[bfs->queue_rear] = neighbour;
	bfs->queue_size = bfs->queue_size + 1;
	bfs->prev[neighbour] = node;
	graph->nodes[neighbour].bfs_marked = TRUE;
	graph->nodes[neighbour].already_enqueued = TRUE;
	return (SUCCESS);
}

size_t			dequeue(t_bfs *bfs)
{
	size_t	index;

	if (is_queue_empty(bfs) == TRUE)
		return (FAILURE);
	index = bfs->queue[bfs->queue_front];
	bfs->queue_front = bfs->queue_front + 1;
	bfs->queue_size = bfs->queue_size - 1;
	return (index);
}

t_bfs			*init_bfs(t_graph *graph)
{
	size_t	i;
	t_bfs	*bfs;

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
		bfs->prev[i] = -1;
		bfs->queue[i] = -1;
		if (graph->nodes[i].source == TRUE)
		{
			bfs->queue[0] = i;
			bfs->queue_size = 1;
			graph->nodes[i].bfs_marked = TRUE;
			graph->nodes[i].already_enqueued = TRUE;
		}
		i++;
	}
	bfs->shortest_path = NULL;
	return (bfs);
}
