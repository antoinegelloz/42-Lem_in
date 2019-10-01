/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/01 16:44:08 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define INCREASE 1
#define DECREASE -1

int8_t	change_capacity(t_graph *graph, t_list *u, t_list *v, int8_t order)
{
	t_edge *curr;

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
	printf("new cap %zd->%zd: %zd\n", *(size_t *)u->content, *(size_t *)v->content, curr->capacity);
	return (SUCCESS);
}

t_bfs			*bfs_disjoint_paths(t_graph *graph)
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
		print_graph(graph);
		node = dequeue(bfs);
		neighbours = graph->nodes[node].head;	
		while (neighbours != NULL && graph->nodes[node].sink == FALSE)
		{
			printf("node: %zd, neigh:%zd, mark:%d, cap:%zd\n", node, neighbours->dest, graph->nodes[neighbours->dest].bfs_marked, neighbours->capacity);
			if (backward == FALSE)
			{
				if (graph->nodes[neighbours->dest].bfs_marked != TRUE && neighbours->capacity > 0)
				{
					enqueue(bfs, neighbours->dest);
					bfs->prev[neighbours->dest] = node;
					graph->nodes[neighbours->dest].bfs_marked = TRUE;
					neighbours = NULL;
				}
				else if (graph->nodes[neighbours->dest].bfs_marked == TRUE && neighbours->capacity > 0)
				{
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
				while (neighbours2 != NULL && (graph->nodes[neighbours2->dest].bfs_marked == FALSE || neighbours2->capacity != 2))
						neighbours2 = neighbours2->next;
				enqueue(bfs, neighbours2->dest);
				bfs->prev[neighbours2->dest] = node;
				backward = FALSE;
				neighbours = NULL;
			}
			print_results(bfs, graph->size);
		}
	}
	print_results(bfs, graph->size);
	return (reconstruct_path(bfs, graph));
}

t_list	*find_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	t_bfs *new_bfs;
	print_ssize_t(aug_paths);
	ft_putendl("********************************************");
	print_graph(graph);
	if ((new_bfs = bfs_disjoint_paths(graph)) == NULL)
		return (aug_paths);
	print_ssize_t(aug_paths);
	ft_putendl("New modified bfs path found");
	print_ssize_t(new_bfs->shortest_path);
	free_bfs(new_bfs);
	return (aug_paths);
}

t_list	*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_list	*curr_path;
	t_bfs	*new_bfs;
	t_list	*curr_path_node;

	aug_paths = NULL;
	curr_path = NULL;
	new_bfs = NULL;
	curr_path_node = NULL;
	while (TRUE)
	{
		if ((new_bfs = bfs(graph)) == NULL)
			return (find_disjoint_paths(graph, aug_paths));
		ft_putendl("New shortest path found");
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
