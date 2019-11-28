/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_disjoint_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 17:50:33 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
				&& graph->nodes[neigh2->dest].enqueued == FALSE)
			enqueue(neigh->dest, neigh2->dest, graph, new_bfs);
		neigh2 = neigh2->next;
	}
}

void	enqueue_node(t_graph *graph, t_list *path,
		t_edge *neigh, t_bfs *new_bfs)
{
	if (graph->nodes[neigh->dest].enqueued == FALSE)
	{
		if (is_on_path(new_bfs->node, path, graph) == FALSE
				&& new_bfs->node != graph->sink)
		{
			if (is_on_path(neigh->dest, path, graph) == TRUE)
				skip_node(new_bfs, neigh, graph, path);
			else if (graph->nodes[neigh->dest].bfs_marked == FALSE)
				enqueue(new_bfs->node, neigh->dest, graph, new_bfs);
		}
		else if (is_on_path(new_bfs->node, path, graph) == TRUE
				&& ((neigh->capacity == 2 && neigh->dest != graph->source)
				|| (neigh->capacity == 1
				&& graph->nodes[neigh->dest].bfs_marked == FALSE)))
			enqueue(new_bfs->node, neigh->dest, graph, new_bfs);
	}
}

t_bfs	*bfs_disjoint_paths(t_graph *graph, t_list *path)
{
	t_bfs	*new_bfs;
	t_edge	*neighbours;

	neighbours = NULL;
	new_bfs = init_bfs(graph);
	while (is_queue_empty(new_bfs) == FALSE)
	{
		new_bfs->node = dequeue(new_bfs);
		neighbours = graph->nodes[new_bfs->node].head;
		while (neighbours != NULL)
		{
			enqueue_node(graph, path, neighbours, new_bfs);
			neighbours = neighbours->next;
		}
	}
	return (reconstruct_path(new_bfs, graph));
}

t_list	*edmonds_disjoint_paths(t_graph *graph,
		t_list *aug_paths, t_list **path)
{
	t_bfs	*new_bfs;
	size_t	path_pos;

	path_pos = compute_path_pos(path, aug_paths, graph);
	new_bfs = NULL;
	if ((new_bfs = bfs_disjoint_paths(graph, *path)) == NULL)
		return (aug_paths);
	graph->paths_count++;
	update_edge_capacities(new_bfs, graph, TRUE);
	ft_lstdel(&aug_paths, ft_delcontent);
	aug_paths = rebuild_aug_paths(graph);
	if (is_new_solution_better(aug_paths, graph) == FALSE)
	{
		graph->paths_count--;
		update_edge_capacities(new_bfs, graph, FALSE);
		ft_lstdel(&aug_paths, ft_delcontent);
		aug_paths = rebuild_aug_paths(graph);
		*path = aug_paths;
		while (path_pos-- > 0)
			*path = get_next_path(*path, graph);
	}
	free_bfs(new_bfs);
	return (aug_paths);
}

t_list	*find_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	t_list		*path;
	t_list		*new_aug_paths;
	size_t		prev_paths_count;
	t_paths		*paths;

	paths = NULL;
	if ((paths = init_output(graph, paths, aug_paths)) == NULL)
		return (NULL);
	compute_output_lines(paths, graph);
	path = aug_paths;
	new_aug_paths = aug_paths;
	while (path != NULL)
	{
		prev_paths_count = graph->paths_count;
		new_aug_paths = edmonds_disjoint_paths(graph, new_aug_paths, &path);
		if (prev_paths_count == graph->paths_count)
		{
			if ((path = get_next_path(path, graph)) == NULL)
				return (new_aug_paths);
		}
		else
			path = new_aug_paths;
	}
	return (new_aug_paths);
}
