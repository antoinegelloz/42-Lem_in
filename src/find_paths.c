/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 23:36:11 by agelloz          ###   ########.fr       */
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

t_bfs	*bfs(t_graph *graph, t_list *path)
{
	t_bfs	*new_bfs;
	t_edge	*neighbours;

	neighbours = NULL;
	new_bfs = init_bfs(graph);
	while (new_bfs->queue_size > 0)
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

t_list	*edmonds_karp(t_graph *graph,
		t_list *aug_paths, t_list **path)
{
	t_bfs	*new_bfs;
	size_t	path_pos;

	path_pos = compute_path_pos(path, aug_paths, graph);
	new_bfs = NULL;
	if ((new_bfs = bfs(graph, *path)) == NULL)
		return (aug_paths);
	update_edge_capacities(new_bfs, graph, INCREASE);
	ft_lstdel(&aug_paths, ft_delcontent);
	aug_paths = rebuild_paths(graph);
	if (is_new_solution_better(aug_paths, graph) == FALSE)
	{
		update_edge_capacities(new_bfs, graph, DECREASE);
		ft_lstdel(&aug_paths, ft_delcontent);
		aug_paths = rebuild_paths(graph);
		*path = aug_paths;
		while (path_pos-- > 0)
			*path = get_next_path(*path, graph);
	}
	free_bfs(new_bfs);
	return (aug_paths);
}

t_list	*first_bfs(t_graph *graph)
{
	t_list	*aug_paths;
	t_bfs	*new_bfs;
	t_paths *paths;

	aug_paths = NULL;
	if ((new_bfs = bfs(graph, NULL)) == NULL)
		return (NULL);
	ft_lstappend(&aug_paths, new_bfs->shortest_path);
	update_edge_capacities(new_bfs, graph, INCREASE);
	free_bfs(new_bfs);
	if ((paths = find_solution(graph, aug_paths)) == NULL)
		return (NULL);
	graph->old_output_lines = paths->output_lines;
	free_paths(paths, graph);
	return (aug_paths);
}

t_list	*find_paths(t_graph *graph)
{
	t_list		*path;
	t_list		*aug_paths;
	size_t		prev_paths_count;

	if ((aug_paths = first_bfs(graph)) == NULL)
		return (NULL);
	path = aug_paths;
	while (path != NULL)
	{
		prev_paths_count = graph->paths_count;
		aug_paths = edmonds_karp(graph, aug_paths, &path);
		if (prev_paths_count == graph->paths_count)
		{
			if ((path = get_next_path(path, graph)) == NULL)
				return (aug_paths);
		}
		else
			path = aug_paths;
	}
	return (aug_paths);
}
