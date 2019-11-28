/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_disjoint_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 16:31:24 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tmp_paths(t_paths *paths, t_graph *graph)
{
	size_t i;

	i = 0;
	while (i < graph->paths_count)
	{
		ft_lstdel(&paths->array[i], ft_delcontent);
		i++;
	}
	free(paths->array);
	free(paths->ants_to_paths);
	free(paths->n);
	free(paths->len);
	free(paths);
}

t_list	*build_path(t_edge *neighbours, t_graph *graph, t_list *new_aug_paths)
{
	t_list *tmp;

	tmp = NULL;
	while (neighbours->dest != graph->sink)
	{
		if (neighbours->capacity == 0)
		{
			if ((tmp = ft_lstnew(&neighbours->dest, sizeof(size_t))) == NULL)
				return (NULL);
			ft_lstappend(&new_aug_paths, tmp);
			neighbours = graph->nodes[neighbours->dest].head;
		}
		else
			neighbours = neighbours->next;
		if (neighbours->dest == graph->sink
				&& neighbours->capacity == 0)
		{
			if ((tmp = ft_lstnew(&neighbours->dest, sizeof(size_t))) == NULL)
				return (NULL);
			ft_lstappend(&new_aug_paths, tmp);
		}
	}
	return (new_aug_paths);
}

t_list	*rebuild_aug_paths(t_graph *graph)
{
	t_list		*new_aug_paths;
	t_list		*tmp;
	t_edge		*first_nodes;
	t_edge		*neighbours;

	new_aug_paths = NULL;
	tmp = NULL;
	first_nodes = graph->nodes[graph->source].head;
	while (first_nodes != NULL)
	{
		if (first_nodes->capacity == 0)
		{
			if ((tmp = ft_lstnew(&graph->source, sizeof(size_t))) == NULL)
				return (NULL);
			ft_lstappend(&new_aug_paths, tmp);
			if ((tmp = ft_lstnew(&first_nodes->dest, sizeof(size_t))) == NULL)
				return (NULL);
			ft_lstappend(&new_aug_paths, tmp);
			neighbours = graph->nodes[first_nodes->dest].head;
			new_aug_paths = build_path(neighbours, graph, new_aug_paths);
		}
		first_nodes = first_nodes->next;
	}
	return (new_aug_paths);
}

int8_t	is_new_solution_better(t_list *aug_paths, t_graph *graph)
{
	t_paths		*paths;
	size_t		new_output_lines;
	size_t		i;

	i = 0;
	paths = NULL;
	new_output_lines = 0;
	if ((paths = init_output(graph, paths, aug_paths)) == NULL)
		return (FAILURE);
	init_lines(paths, graph);
	while (is_solution_found(paths, graph) == FALSE)
	{
		i = 0;
		while (i < graph->paths_count)
			paths->n[i++] = 0;
		paths->output_lines++;
	}
	new_output_lines = paths->output_lines;
	free_tmp_paths(paths, graph);
	if (new_output_lines < graph->old_output_lines)
	{
		graph->old_output_lines = new_output_lines;
		return (TRUE);
	}
	return (FALSE);
}

size_t	is_on_path(size_t node, t_list *path, t_graph *graph)
{
	t_list	*curr;

	curr = path;
	while (curr != NULL && *(size_t *)curr->content != graph->sink)
	{
		if (*(size_t *)curr->content == node
				&& node != graph->source && node != graph->sink)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

void	skip_nodeonpath(t_bfs *new_bfs, t_edge *neigh, t_graph *graph, t_list *path)
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
				skip_nodeonpath(new_bfs, neigh, graph, path);
			else if (graph->nodes[neigh->dest].bfs_marked == FALSE)
				enqueue(new_bfs->node, neigh->dest, graph, new_bfs);
		}
		else if (is_on_path(new_bfs->node, path, graph) == TRUE
						&& ((neigh->capacity == 2 && neigh->dest != graph->source)
							|| (neigh->capacity == 1 && graph->nodes[neigh->dest].bfs_marked == FALSE)))
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

t_list	*get_next_path(t_list *path, t_graph *graph)
{
	t_list	*next_path;

	next_path = path;
	while (next_path->next != NULL &&
			*(size_t *)next_path->next->content != graph->source)
		next_path = next_path->next;
	next_path = next_path->next;
	return (next_path);
}

size_t	compute_path_pos(t_list **path, t_list *aug_paths, t_graph *graph)
{
	size_t	path_pos;
	t_list	*curr;

	path_pos = 0;
	curr = aug_paths;
	while (curr != *path)
	{
		if (*(size_t *)curr->content == graph->source)
			path_pos++;
		curr = curr->next;
	}
	return (path_pos);
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
