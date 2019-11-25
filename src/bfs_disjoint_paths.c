/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_disjoint_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/25 17:50:24 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*rebuild_paths(t_graph *graph)
{
	t_list		*new_aug_paths;
	t_list		*tmp;
	t_edge		*neighbours;
	t_edge		*neighbours2;
	size_t		node;

	new_aug_paths = NULL;
	tmp = NULL;
	node = graph->source;
	neighbours = graph->nodes[graph->source].head;
	while (neighbours != NULL)
	{
		if (neighbours->capacity == 0)
		{
			tmp = ft_lstnew(&graph->source, sizeof(size_t));
			ft_lstappend(&new_aug_paths, tmp);
			node = neighbours->dest;
			tmp = ft_lstnew(&node, sizeof(size_t));
			ft_lstappend(&new_aug_paths, tmp);
			neighbours2 = graph->nodes[node].head;
			while (node != graph->sink)
			{
				if (neighbours2->capacity == 0)
				{
					node = neighbours2->dest;
					tmp = ft_lstnew(&node, sizeof(size_t));
					ft_lstappend(&new_aug_paths, tmp);
					neighbours2 = graph->nodes[node].head;
				}
				else
					neighbours2 = neighbours2->next;
			}
		}
		neighbours = neighbours->next;
	}
	return (new_aug_paths);
}

size_t	is_on_path(size_t node, t_list *prev_path, t_graph *graph)
{
	t_list	*curr;

	curr = prev_path;
	while (curr != NULL)
	{
		if (*(size_t *)curr->content == node
				&& node != graph->source && node != graph->sink)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

t_list	*bfs_disjoint_paths(t_graph *graph, t_list *aug_paths, t_list *prev_path)
{
	t_bfs	*new_bfs;
	t_edge	*neighbours;
	t_edge	*neighbours2;
	size_t	node;
	int8_t	node_on_path;
	t_list	*new_aug_paths;
	t_list	*curr;

	ft_putendl("BFS DISJ");
	new_aug_paths = NULL;
	neighbours = NULL;
	new_bfs = init_bfs(graph);
	while (is_queue_empty(new_bfs) == FALSE)
	{
		node = dequeue(new_bfs);
		//ft_printf(">> DEQ node : %s \n", graph->nodes[node].name);
		node_on_path = is_on_path(node, prev_path, graph);
		neighbours = graph->nodes[node].head;
		while (neighbours != NULL)
		{
			if (graph->nodes[neighbours->dest].already_enqueued == FALSE)
			{
				if (node_on_path == FALSE && node != graph->sink)
				{
					if (is_on_path(neighbours->dest, prev_path, graph) == TRUE)
					{
						new_bfs->prev[neighbours->dest] = node;
						graph->nodes[neighbours->dest].bfs_marked = TRUE;
						graph->nodes[neighbours->dest].already_enqueued = TRUE;
						neighbours2 = graph->nodes[neighbours->dest].head;
						while (neighbours2)
						{
							if (neighbours2->capacity == 2 && is_on_path(neighbours2->dest, prev_path, graph) == TRUE)
							{
								enqueue(neighbours->dest, neighbours2->dest, graph, new_bfs);
								//ft_printf("EQ first backward : %s \n", graph->nodes[neighbours2->dest].name);
							}
							neighbours2 = neighbours2->next;
						}
					}
					else
					{
						enqueue(node, neighbours->dest, graph, new_bfs);
						//ft_printf("EQ normal : %s \n", graph->nodes[neighbours->dest].name);
					}
				}
				else if (node_on_path == TRUE && neighbours->capacity == 2 && neighbours->dest != graph->source)
				{
					enqueue(node, neighbours->dest, graph, new_bfs);
					//ft_printf("EQ backward: %s \n", graph->nodes[neighbours->dest].name);
				}
				else if (node_on_path == TRUE && neighbours->capacity == 1)
				{
					enqueue(node, neighbours->dest, graph, new_bfs);
					//ft_printf("EQ excape: %s \n", graph->nodes[neighbours->dest].name);
				}
			}
			neighbours = neighbours->next;
		}
	}
	if ((new_bfs = reconstruct_path(new_bfs, graph)) == NULL)
		return (aug_paths);
	curr = new_bfs->shortest_path;
	while (curr->next != NULL)
	{
		change_capacity(graph, curr, curr->next, DECREASE);
		change_capacity(graph, curr->next, curr, INCREASE);
		curr = curr->next;
	}
	ft_lstdel(&aug_paths, ft_delcontent);
	new_aug_paths = rebuild_paths(graph);
	graph->paths_count++;
	reset_marks(graph, new_bfs);
	free_bfs(new_bfs);
	return (new_aug_paths);
}

/*// If disjoint paths are found, check whether the new solution is better. If not, stop, 
	// or start a new bfs disjoint from another neighbour of start.
	if (is_new_solution_better(new_bfs, graph, aug_paths) == FALSE)
	{
		reset_marks(graph, new_bfs);
		return (aug_paths);
	}*/

/*int8_t	compare_solution(t_bfs *bfs, t_graph *graph, t_list *aug_paths)
{
	size_t old_output_lines;
	size_t new_output_lines;

	old_output_lines = 0;
	new_output_lines = 0;
	(void)bfs;
	(void)graph;
	(void)aug_paths;
	// To do:
	// compute old and new output_lines
	// if (new_output_lines > old_output_lines)
	//	return (FALSE);
	return (TRUE);
}*/
