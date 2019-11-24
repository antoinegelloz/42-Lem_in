/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_disjoint_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/24 21:28:29 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	is_on_path(size_t node, t_list *aug_paths, t_graph *graph)
{
	t_list	*curr;

	curr = aug_paths;
	while (curr != NULL)
	{
		if (*(size_t *)curr->content == node
				&& node != graph->source && node != graph->sink)
		{
			//ft_printf("node %s on path\n", graph->nodes[node].name);
			return (TRUE);
		}
		curr = curr->next;
	}
	return (FALSE);
}

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

t_bfs	*reconstruct_path_from(size_t node_from, t_bfs *bfs, t_graph *graph)
{
	t_list	*tmp;
	ssize_t	i;

	tmp = NULL;
	i = graph->size - 1;
	while (graph->nodes[i].sink == FALSE)
		i--;
	while (i != -1)
	{
		tmp = ft_lstnew(&i, sizeof(ssize_t));
		ft_lstadd(&bfs->shortest_path, tmp);
		i = bfs->prev[i];
	}
	if (*(size_t *)bfs->shortest_path->content != node_from)
	{
		reset_marks_fail(graph, bfs, FALSE);
		ft_lstdel(&bfs->shortest_path, ft_delcontent);
		free_bfs(bfs);
		return (NULL);
	}
	reset_marks(graph, bfs, FALSE);
	return (bfs);
}

t_bfs	*bfs_from(size_t node_from, t_graph *graph)
{
	size_t	node;
	t_bfs	*bfs;
	t_edge	*neighbours;

	neighbours = NULL;
	bfs = init_bfs(graph);
	bfs->queue[0] = node_from;
	bfs->queue_size = 1;
	bfs->paths_crossed = 0;
	graph->nodes[node_from].tmp_marked = TRUE;
	while (is_queue_empty(bfs) == FALSE)
	{
		node = dequeue(bfs);
		neighbours = graph->nodes[node].head;
		while (neighbours)
		{
			if (graph->nodes[neighbours->dest].tmp_marked == FALSE
				&& graph->nodes[neighbours->dest].bfs_marked == FALSE
				&& neighbours->capacity > 0)
			{
				enqueue(bfs, neighbours->dest);
				bfs->prev[neighbours->dest] = node;
				graph->nodes[neighbours->dest].tmp_marked = TRUE;
			}
			neighbours = neighbours->next;
		}
	}
	return (reconstruct_path_from(node_from, bfs, graph));
}

size_t	can_we_escape_from(size_t node, t_graph *graph, t_bfs *bfs)
{
	t_edge		*neighbours;
	t_bfs		*new_bfs_from;
	t_list		*path_node;

	neighbours = graph->nodes[node].head;
	while (neighbours != NULL)
	{
		if (graph->nodes[neighbours->dest].bfs_marked == FALSE)
		{
			if ((new_bfs_from = bfs_from(neighbours->dest, graph)) != NULL)
			{
				path_node = new_bfs_from->shortest_path;
				bfs->prev[*(size_t *)path_node->content] = node;
				graph->nodes[*(size_t *)path_node->content].bfs_marked = TRUE;
				while (path_node->next != NULL)
				{
					bfs->prev[*(size_t *)path_node->next->content] = *(size_t *)path_node->content;
					graph->nodes[*(size_t *)path_node->next->content].bfs_marked = TRUE;
					path_node = path_node->next;
				}
				return (TRUE);
			}
			return (FALSE);
		}
		neighbours = neighbours->next;
	}
	return (FALSE);
}

void	enqueue_neighbour(size_t node, size_t neighbour, t_graph *graph, t_bfs *bfs)
{
	enqueue(bfs, neighbour);
	bfs->prev[neighbour] = node;
	graph->nodes[neighbour].bfs_marked = TRUE;
	graph->nodes[neighbour].already_enqueued = TRUE;
}

t_bfs	*bfs_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	t_bfs	*bfs;
	t_edge	*neighbours;
	t_edge	*neighbours2;
	size_t	node;
	int8_t	node_on_path;

	neighbours = NULL;
	bfs = init_bfs(graph);
	while (is_queue_empty(bfs) == FALSE)
	{
		node = dequeue(bfs);
		node_on_path = is_on_path(node, aug_paths, graph);
		neighbours = graph->nodes[node].head;
		while (neighbours != NULL)
		{
			if (graph->nodes[neighbours->dest].already_enqueued == FALSE)
			{
				if (node_on_path == FALSE)
				{
					if (is_on_path(neighbours->dest, aug_paths, graph) == FALSE)
						enqueue_neighbour(node, neighbours->dest, graph, bfs);
					else
					{
						bfs->prev[neighbours->dest] = node;
						graph->nodes[neighbours->dest].bfs_marked = TRUE;
						graph->nodes[neighbours->dest].already_enqueued = TRUE;
						neighbours2 = graph->nodes[neighbours->dest].head;
						while (neighbours2)
						{
							if (neighbours2->capacity == 2 && is_on_path(neighbours2->dest, aug_paths, graph) == TRUE)
								enqueue_neighbour(neighbours->dest, neighbours2->dest, graph, bfs);
							neighbours2 = neighbours2->next;
						}
					}
				}
				else if (node_on_path == TRUE && neighbours->capacity == 2)
				{
					if (can_we_escape_from(neighbours->dest, graph, bfs) == TRUE)
					{
						bfs->prev[neighbours->dest] = node;
						graph->nodes[neighbours->dest].bfs_marked = TRUE;
						return (reconstruct_path(bfs, graph));
					}
					else
						enqueue_neighbour(node, neighbours->dest, graph, bfs);
					break ;
				}
			}
			neighbours = neighbours->next;
		}
	}
	return (reconstruct_path(bfs, graph));
}

int8_t	is_new_solution_better(t_bfs *bfs, t_graph *graph, t_list *aug_paths)
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
}

t_list	*find_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	t_bfs	*new_bfs;
	t_list	*curr_path_node;

	while (TRUE)
	{
		if ((new_bfs = bfs_disjoint_paths(graph, aug_paths)) == NULL)
			return (aug_paths);

		// If disjoint paths are found, check whether the new solution is better. If not, stop, 
		// or start a new bfs disjoint from another neighbour of start.
		if (is_new_solution_better(new_bfs, graph, aug_paths) == FALSE)
			return (aug_paths);

		curr_path_node = new_bfs->shortest_path;
		while (curr_path_node->next != NULL)
		{
			change_capacity(graph, curr_path_node, curr_path_node->next, DECREASE);
			change_capacity(graph, curr_path_node->next, curr_path_node, INCREASE);
			curr_path_node = curr_path_node->next;
		}
		ft_lstdel(&aug_paths, ft_delcontent);
		aug_paths = rebuild_paths(graph);
		free_bfs(new_bfs);
	}
	return (aug_paths);
}
