/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_reset_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:12:29 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/19 18:12:06 by agelloz          ###   ########.fr       */
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
				graph->nodes[i].tmp_marked = FALSE;
			j++;
		}
		i++;
	}
}

static int8_t	find_node(t_list *path, size_t i)
{
	t_list	*curr;
	int8_t	found;

	found = FALSE;
	curr = path;
	while (curr != NULL)
	{
		if (i == *(size_t *)curr->content)
		{
			found = TRUE;
			break ;
		}
		curr = curr->next;
	}
	return (found);
}

static int8_t	find_neighbour(t_edge *neighbours, int8_t found)
{
	while (neighbours)
	{
		if (neighbours->capacity == 2)
		{
			found = TRUE;
			break ;
		}
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
	neighbours = NULL;
	found = FALSE;
	while (i < graph->size)
	{
		found = find_node(bfs->shortest_path, i);
		neighbours = graph->nodes[i].head;
		found = find_neighbour(neighbours, found);
		if (found == FALSE || graph->nodes[i].sink == TRUE
				|| graph->nodes[i].source == TRUE)
			graph->nodes[i].bfs_marked = FALSE;
		found = FALSE;
		i++;
	}
}
