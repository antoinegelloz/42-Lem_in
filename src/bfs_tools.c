/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:01:34 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 23:46:21 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t			enqueue(size_t node, size_t neigh, t_graph *graph, t_bfs *bfs)
{
	if (bfs->queue_size == bfs->queue_capacity)
		return (FAILURE);
	bfs->queue_rear = bfs->queue_rear + 1;
	bfs->queue[bfs->queue_rear] = neigh;
	bfs->queue_size = bfs->queue_size + 1;
	bfs->prev[neigh] = node;
	graph->nodes[neigh].bfs_marked = TRUE;
	graph->nodes[neigh].enqueued = TRUE;
	return (SUCCESS);
}

size_t			dequeue(t_bfs *bfs)
{
	size_t	index;

	if (bfs->queue_size == 0)
		return (FAILURE);
	index = bfs->queue[bfs->queue_front];
	bfs->queue_front = bfs->queue_front + 1;
	bfs->queue_size = bfs->queue_size - 1;
	return (index);
}

static t_bfs	*init_bfs2(t_bfs *bfs, t_graph *graph)
{
	bfs->queue_front = 0;
	bfs->queue_size = 0;
	bfs->queue_rear = 0;
	bfs->queue_capacity = graph->size;
	bfs->node = 0;
	bfs->shortest_path = NULL;
	if (!(bfs->queue = malloc(bfs->queue_capacity * sizeof(ssize_t))))
		return (NULL);
	if (!(bfs->prev = malloc(bfs->queue_capacity * sizeof(ssize_t))))
		return (NULL);
	return (bfs);
}

t_bfs			*init_bfs(t_graph *graph)
{
	size_t	i;
	t_bfs	*bfs;

	if ((bfs = (t_bfs *)malloc(sizeof(t_bfs))) == NULL)
		return (NULL);
	if (init_bfs2(bfs, graph) == NULL)
		return (free_bfs(bfs));
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
			graph->nodes[i].enqueued = TRUE;
		}
		i++;
	}
	return (bfs);
}
