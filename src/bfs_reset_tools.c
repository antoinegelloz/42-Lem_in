/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_reset_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:12:29 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 15:36:54 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			reset_marks_fail(t_graph *graph, t_bfs *bfs)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	while (i < (ssize_t)graph->size)
	{
		j = 0;
		while (bfs->queue[j] != -1)
		{
			if (i == bfs->queue[j])
				graph->nodes[i].bfs_marked = FALSE;
			j++;
		}
    graph->nodes[i].enqueued = FALSE;
		i++;
	}
}

static int8_t	find_node(t_list *path, size_t i)
{
	t_list	*curr;

	curr = path;
	while (curr != NULL)
	{
		if (i == *(size_t *)curr->content)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

static int8_t	find_neighbour(t_edge *neighbours, int8_t found)
{
	while (neighbours)
	{
		if (neighbours->capacity == 2)
			return (TRUE);
		neighbours = neighbours->next;
	}
	return (found);
}

void			reset_marks(t_graph *graph, t_bfs *bfs)
{
	size_t	i;
	int8_t	found;
	t_edge	*neighbours;

	i = 0;
	found = FALSE;
	neighbours = NULL;
	while (i < graph->size)
	{
		found = find_node(bfs->shortest_path, i);
		neighbours = graph->nodes[i].head;
		found = find_neighbour(neighbours, found);
		if (found == FALSE || graph->nodes[i].sink == TRUE
						   || graph->nodes[i].source == TRUE)
			graph->nodes[i].bfs_marked = FALSE;
		graph->nodes[i].enqueued = FALSE;
		found = FALSE;
		i++;
	}
}
