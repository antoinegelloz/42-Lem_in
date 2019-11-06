/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/14 16:13:32 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t		change_capacity(t_graph *graph, t_list *u, t_list *v, int8_t order)
{
	t_edge	*curr;

	curr = graph->nodes[*(int *)u->content].head;
	while (curr->dest != *(size_t *)v->content)
		curr = curr->next;
	if (curr->dest == *(size_t *)v->content)
	{
		if (order == INCREASE)
			curr->capacity++;
		if (order == DECREASE)
			curr->capacity--;
	}
	return (SUCCESS);
}

static void	go_backward(t_graph *graph, t_bfs *bfs, size_t node)
{
	if (graph->nodes[bfs->neighbours->dest].bfs_marked != TRUE
			&& bfs->neighbours->capacity > 0)
	{
		enqueue(bfs, bfs->neighbours->dest);
		bfs->prev[bfs->neighbours->dest] = node;
		graph->nodes[bfs->neighbours->dest].bfs_marked = TRUE;
		bfs->neighbours = NULL;
	}
	else if (graph->nodes[bfs->neighbours->dest].bfs_marked == TRUE
			&& bfs->neighbours->capacity > 0
			&& bfs->neighbours->dest != graph->source)
	{
		enqueue(bfs, bfs->neighbours->dest);
		bfs->prev[bfs->neighbours->dest] = node;
		bfs->backward = TRUE;
		bfs->neighbours = NULL;
	}
	if (bfs->neighbours != NULL)
		bfs->neighbours = bfs->neighbours->next;
}

static void	move_bfs(t_graph *graph, t_bfs *bfs, size_t node)
{
	while (bfs->neighbours2 != NULL)
	{
		if (bfs->neighbours2->dest != graph->source
				&& graph->nodes[bfs->neighbours2->dest].bfs_marked == TRUE
				&& bfs->neighbours2->capacity == 2)
		{
			enqueue(bfs, bfs->neighbours2->dest);
			bfs->prev[bfs->neighbours2->dest] = node;
		}
		bfs->neighbours2 = bfs->neighbours2->next;
	}
}

t_bfs		*bfs_disjoint_paths(t_graph *graph)
{
	size_t	node;
	t_bfs	*bfs;

	bfs = init_bfs(graph);
	while (is_queue_empty(bfs) == FALSE)
	{
		node = dequeue(bfs);
		bfs->neighbours = graph->nodes[node].head;
		while (bfs->neighbours != NULL && graph->nodes[node].sink == FALSE
				&& graph->nodes[node].source == FALSE)
		{
			if (bfs->backward == FALSE)
			{
				go_backward(graph, bfs, node);
			}
			else
			{
				bfs->neighbours2 = graph->nodes[node].head;
				move_bfs(graph, bfs, node);
				bfs->backward = FALSE;
				bfs->neighbours = NULL;
			}
		}
	}
	return (reconstruct_path(bfs, graph));
}
