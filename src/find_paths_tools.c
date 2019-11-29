/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:26:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/29 16:05:51 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bfs	*reconstruct_path(t_bfs *new_bfs, t_graph *graph)
{
	t_list	*tmp;
	ssize_t	i;

	i = 0;
	while (graph->nodes[i].sink == FALSE)
		i++;
	while (i != -1)
	{
		if ((tmp = ft_lstnew(&i, sizeof(ssize_t))) == NULL)
			return (NULL);
		ft_lstadd(&new_bfs->shortest_path, tmp);
		i = new_bfs->prev[i];
	}
	if (*(size_t *)new_bfs->shortest_path->content != graph->source)
	{
		reset_marks_fail(graph, new_bfs);
		ft_lstdel(&new_bfs->shortest_path, ft_delcontent);
		free_bfs(new_bfs);
		return (NULL);
	}
	reset_marks(graph, new_bfs);
	return (new_bfs);
}

void	skip_node(t_bfs *new_bfs, t_edge *neigh, t_graph *graph, t_list *path)
{
	t_edge	*neigh2;

	new_bfs->prev[neigh->dest] = new_bfs->node;
	graph->nodes[neigh->dest].bfs_marked = TRUE;
	graph->nodes[neigh->dest].enqueued = TRUE;
	neigh2 = graph->nodes[neigh->dest].head;
	while (neigh2)
	{
		if (neigh2->capacity == 2
				&& is_on_path(neigh2->dest, path, graph) == TRUE
				&& neigh2->dest != graph->source)
		{
			enqueue(neigh->dest, neigh2->dest, graph, new_bfs);
			graph->nodes[neigh2->dest].enqueued_backward = TRUE;
		}
		neigh2 = neigh2->next;
	}
}

int8_t	is_source_neighbours(size_t node, t_graph *graph)
{
	t_edge	*curr;

	curr = graph->nodes[node].head;
	while (curr != NULL)
	{
		if (curr->dest == graph->source)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}
