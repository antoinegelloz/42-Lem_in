/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_reset_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:12:29 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 19:40:44 by agelloz          ###   ########.fr       */
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

static int8_t	find_neighbour(t_graph *graph, size_t i, int8_t found)
{
	t_edge	*neighbours;

	neighbours = graph->nodes[i].head;
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
	t_list	*curr;

	i = 0;
	while (i < graph->size)
	{
		found = FALSE;
		curr = bfs->shortest_path;
		while (curr != NULL)
		{
			if (i == *(size_t *)curr->content)
				found = TRUE;
			curr = curr->next;
		}
		found = find_neighbour(graph, i, found);
		if (found == FALSE || graph->nodes[i].sink == TRUE
			|| graph->nodes[i].source == TRUE)
			graph->nodes[i].bfs_marked = FALSE;
		graph->nodes[i].enqueued = FALSE;
		i++;
	}
}
