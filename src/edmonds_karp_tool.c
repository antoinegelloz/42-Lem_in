/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/19 19:26:13 by agelloz          ###   ########.fr       */
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

int8_t			is_on_path(size_t node, t_list *aug_paths)
{
	t_list *curr;

	curr = aug_paths;
	while (curr != NULL)
	{
		if (*(size_t *)curr->content == node)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

int8_t			can_we_escape_from(size_t node, t_graph *graph)
{
	t_edge		*curr;

	curr = graph->nodes[node].head;
	while (curr != NULL)
	{
		if (graph->nodes[curr->dest].bfs_marked == FALSE)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

t_bfs			*bfs_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	size_t		node;
	t_bfs 		*bfs;
	t_edge		*neighbours;
	t_edge		*neighbours2;
	int8_t		backward;

	neighbours = NULL;
	neighbours2 = NULL;
	bfs = init_bfs(graph);
	backward = FALSE;
	while (is_queue_empty(bfs) == FALSE)
	{
		node = dequeue(bfs);
		neighbours = graph->nodes[node].head;
		while (neighbours != NULL && graph->nodes[node].sink == FALSE)
		{
			if (backward == FALSE)
			{
				if (graph->nodes[neighbours->dest].bfs_marked != TRUE && neighbours->capacity > 0)
				{
					//ft_printf("NOT MARKED %d -> %d mark:%d cap:%d\n", node, neighbours->dest, graph->nodes[neighbours->dest].bfs_marked, neighbours->capacity);
					ft_printf("NOT MARKED %s -> %s mark:%d cap:%d\n", graph->nodes[node].name, graph->nodes[neighbours->dest].name, graph->nodes[neighbours->dest].bfs_marked, neighbours->capacity);
					enqueue(bfs, neighbours->dest);
					bfs->prev[neighbours->dest] = node;
					graph->nodes[neighbours->dest].bfs_marked = TRUE;
					neighbours = NULL;
				}
				else if (graph->nodes[neighbours->dest].bfs_marked == TRUE && neighbours->capacity > 0 && neighbours->dest != graph->source
						&& is_on_path(neighbours->dest, aug_paths) == TRUE)
				{
					ft_printf("MARKED %s -> %s mark:%d cap:%d\n", graph->nodes[node].name, graph->nodes[neighbours->dest].name, graph->nodes[neighbours->dest].bfs_marked, neighbours->capacity);
					//ft_printf("MARKED %d -> %d mark:%d cap:%d\n", node, neighbours->dest, graph->nodes[neighbours->dest].bfs_marked, neighbours->capacity);
					enqueue(bfs, neighbours->dest);
					bfs->prev[neighbours->dest] = node;
					backward = TRUE;
					neighbours = NULL;
				}
				if (neighbours != NULL)
					neighbours = neighbours->next;
			}
			else
			{
				neighbours2 = graph->nodes[node].head;
				while (neighbours2 != NULL)
				{
					if (neighbours2->dest != graph->source
							&& graph->nodes[neighbours2->dest].bfs_marked == TRUE
							&& neighbours2->capacity == 2)
					{
						ft_printf("BACK %s -> %s mark:%d cap:%d\n", graph->nodes[node].name, graph->nodes[neighbours2->dest].name, graph->nodes[neighbours2->dest].bfs_marked, neighbours2->capacity);
						//ft_printf("BACK %d -> %d mark:%d cap:%d\n", node, neighbours2->dest, graph->nodes[neighbours2->dest].bfs_marked, neighbours2->capacity);
						enqueue(bfs, neighbours2->dest);
						bfs->prev[neighbours2->dest] = node;
					}
					neighbours2 = neighbours2->next;
					if (neighbours2 != NULL && can_we_escape_from(neighbours2->dest, graph) == TRUE)
						backward = FALSE;
				}
				neighbours = NULL;
			}
		}
	}
	return (reconstruct_path(bfs, graph));
}

t_list	*find_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	t_bfs	*new_bfs;
	t_list	*curr_path_node;

	if ((new_bfs = bfs_disjoint_paths(graph, aug_paths)) == NULL)
		return (aug_paths);
	//else
	//	ft_printf("SUCCESS\n");
	ft_lstappend(&aug_paths, new_bfs->shortest_path);
	curr_path_node = new_bfs->shortest_path;
	while (curr_path_node->next != NULL)
	{
		change_capacity(graph, curr_path_node, curr_path_node->next, DECREASE);
		change_capacity(graph, curr_path_node->next, curr_path_node, INCREASE);
		curr_path_node = curr_path_node->next;
	}
	free_bfs(new_bfs);
	return (aug_paths);
}
