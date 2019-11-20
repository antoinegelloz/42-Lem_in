/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/20 18:09:03 by ekelkel          ###   ########.fr       */
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
		//ft_printf("neighbour:%d, mark:%d\n", curr->dest, graph->nodes[curr->dest].bfs_marked);
		if (graph->nodes[curr->dest].bfs_marked == FALSE)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

int8_t			enqueue_neighbours(t_edge *neigh, t_bfs *bfs, t_graph *graph, t_list *aug_paths, size_t node)
{
	t_edge *curr;
	t_edge *neighbours2;

	curr = neigh;
	if (bfs->backward == TRUE && can_we_escape_from(node, graph) == TRUE)
	{
		//ft_putendl("ESCAPE");
		bfs->backward = FALSE;
		neighbours2 = graph->nodes[node].head;
		while (neighbours2 != NULL)
		{
			if (graph->nodes[neighbours2->dest].bfs_marked == FALSE)
			{
				enqueue(bfs, neighbours2->dest);
				graph->nodes[neighbours2->dest].already_enqueued = TRUE;
				graph->nodes[neighbours2->dest].bfs_marked = TRUE;
				bfs->prev[neighbours2->dest] = node;
				//ft_printf("q:%d\n", curr->dest);
				return (1);
			}
			neighbours2 = neighbours2->next;
		}
	}
	else 
	{
		while (curr != NULL)
		{
			if ((graph->nodes[curr->dest].bfs_marked == FALSE || (is_on_path(curr->dest, aug_paths) == TRUE && curr->capacity > 0)) &&
					graph->nodes[curr->dest].already_enqueued == FALSE)
			{
				enqueue(bfs, curr->dest);
				graph->nodes[curr->dest].already_enqueued = TRUE;
				graph->nodes[curr->dest].bfs_marked = TRUE;
				bfs->prev[curr->dest] = node;
				if (is_on_path(curr->dest, aug_paths) == TRUE && graph->nodes[curr->dest].source == FALSE)
					bfs->backward = TRUE;
				//ft_printf("q:%d\n", curr->dest);
			}
			curr = curr->next;
		}
	}
	return (0);
}
void			init_already_enqueued(t_graph *graph)
{
	size_t i;

	i = 0;
	while (i < graph->size)
	{
		if (i != graph->source)
			graph->nodes[i].already_enqueued = FALSE;
		i++;
	}
}

t_bfs			*bfs_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	size_t		node;
	t_bfs 		*bfs;
	t_edge		*neighbours;
	t_edge		*neighbours2;
	int8_t		result;


	neighbours = NULL;
	neighbours2 = NULL;
	bfs = init_bfs(graph);
	bfs->backward = FALSE;
	init_already_enqueued(graph);
	while (is_queue_empty(bfs) == FALSE)
	{
		node = dequeue(bfs);
		neighbours = graph->nodes[node].head;
		while (neighbours != NULL && graph->nodes[node].sink == FALSE)
		{
			//ft_putendl("QQ");
			result = enqueue_neighbours(neighbours, bfs, graph, aug_paths, node);
			if (result == 1)
				break;
			neighbours = neighbours->next;
		}
	}
	return (reconstruct_path(bfs, graph));
}

t_list	*find_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	t_bfs	*new_bfs;
	t_list	*curr_path_node;

	while (TRUE)
	{
		if ((new_bfs = bfs_disjoint_paths(graph, aug_paths)) == NULL)
			return (aug_paths);
		ft_lstappend(&aug_paths, new_bfs->shortest_path);
		curr_path_node = new_bfs->shortest_path;
		while (curr_path_node->next != NULL)
		{
			change_capacity(graph, curr_path_node, curr_path_node->next, DECREASE);
			change_capacity(graph, curr_path_node->next, curr_path_node, INCREASE);
			curr_path_node = curr_path_node->next;
		}
		free_bfs(new_bfs);
	}
	return (aug_paths);
}
