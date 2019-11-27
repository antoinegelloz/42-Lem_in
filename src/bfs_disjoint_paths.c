/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_disjoint_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/27 14:15:08 by ekelkel          ###   ########.fr       */
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
			tmp = ft_lstnew(&graph->source, sizeof(size_t));
			ft_lstappend(&new_aug_paths, tmp);
			tmp = ft_lstnew(&first_nodes->dest, sizeof(size_t));
			ft_lstappend(&new_aug_paths, tmp);
			neighbours = graph->nodes[first_nodes->dest].head;
			while (neighbours->dest != graph->sink)
			{
				if (neighbours->capacity == 0)
				{
					tmp = ft_lstnew(&neighbours->dest, sizeof(size_t));
					ft_lstappend(&new_aug_paths, tmp);
					neighbours = graph->nodes[neighbours->dest].head;
				}
				else
					neighbours = neighbours->next;
				//if (neighbours == NULL)
				//	ft_printf("NULL:%s\n", graph->nodes[first_nodes->dest].name);
				if (neighbours->dest == graph->sink && neighbours->capacity == 0)
				{
					tmp = ft_lstnew(&neighbours->dest, sizeof(size_t));
					ft_lstappend(&new_aug_paths, tmp);
				}
			}

		}
		first_nodes = first_nodes->next;
	}
	//ft_putendl(">>> REBUILD:");
	//print_ssize_t(new_aug_paths, graph);
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
	//ft_printf("new:%d, old:%d\n", new_output_lines, graph->old_output_lines);
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

int8_t	is_sink_neighbour(size_t node, t_graph *graph)
{
	t_edge	*curr;

	curr = graph->nodes[node].head;
	while (curr != NULL)
	{
		if (curr->dest == graph->sink)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

t_bfs   *bfs_disjoint_paths(t_graph *graph, t_list *path)
{
	t_bfs	*new_bfs;
	t_edge	*neighbours;
	t_edge	*neighbours2;
	size_t	node;
	int8_t	node_on_path;

	//ft_putendl("BFS DISJ");
	neighbours = NULL;
	new_bfs = init_bfs(graph);
	while (is_queue_empty(new_bfs) == FALSE)
	{
		node = dequeue(new_bfs);
		node_on_path = is_on_path(node, path, graph);
		neighbours = graph->nodes[node].head;
		while (neighbours != NULL)
		{
			if (graph->nodes[neighbours->dest].already_enqueued == FALSE)
			{
				if (node_on_path == FALSE && node != graph->sink)
				{
					if (is_on_path(neighbours->dest, path, graph) == TRUE && is_sink_neighbour(neighbours->dest, graph) == FALSE)
					{
						new_bfs->prev[neighbours->dest] = node;
						graph->nodes[neighbours->dest].bfs_marked = TRUE;
						graph->nodes[neighbours->dest].already_enqueued = TRUE;
						neighbours2 = graph->nodes[neighbours->dest].head;
						while (neighbours2)
						{
							if (neighbours2->capacity == 2 && is_on_path(neighbours2->dest, path, graph) == TRUE
									&& graph->nodes[neighbours2->dest].already_enqueued == FALSE)
								enqueue(neighbours->dest, neighbours2->dest, graph, new_bfs);
							neighbours2 = neighbours2->next;
						}
					}
					else if (graph->nodes[neighbours->dest].bfs_marked == FALSE)
						enqueue(node, neighbours->dest, graph, new_bfs);
				}
				else if (node_on_path == TRUE
						&& ((neighbours->capacity == 2 && neighbours->dest != graph->source)
							|| (neighbours->capacity == 1 && graph->nodes[neighbours->dest].bfs_marked == FALSE)))
					enqueue(node, neighbours->dest, graph, new_bfs);
			}
			neighbours = neighbours->next;
		}
	}
	return (reconstruct_path(new_bfs, graph));
}

t_list  *get_next_path(t_list *path, t_graph *graph)
{
	t_list  *next_path;

	next_path = path;
	while (next_path->next != NULL &&
			*(size_t *)next_path->next->content != graph->source)
		next_path = next_path->next;
	next_path = next_path->next;
	return (next_path);
}

t_list *edmonds_disjoint_paths(t_graph *graph, t_list *aug_paths, t_list **path)
{
	t_bfs	*new_bfs;
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
	new_bfs = NULL;
	if ((new_bfs = bfs_disjoint_paths(graph, *path)) == NULL)
		return (aug_paths);
	graph->paths_count++;
	update_edge_capacities(new_bfs, graph, TRUE);
	ft_lstdel(&aug_paths, ft_delcontent);
	aug_paths = rebuild_aug_paths(graph);
	if (is_new_solution_better(aug_paths, graph) == FALSE)
	{
		//print_ssize_t(aug_paths, graph);
		graph->paths_count--;
		update_edge_capacities(new_bfs, graph, FALSE);
		ft_lstdel(&aug_paths, ft_delcontent);
		aug_paths = rebuild_aug_paths(graph);
		//print_ssize_t(aug_paths, graph);
		*path = aug_paths;
		while (path_pos > 0)
		{
			*path = get_next_path(*path, graph);
			path_pos--;
		}
	}
	free_bfs(new_bfs);
	return (aug_paths);
}

t_list *find_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	t_list		*path;
	t_list		*new_aug_paths;
	size_t		prev_paths_count;
	t_paths		*paths;
	size_t		i;

	i = 0;
	paths = NULL;
	if ((paths = init_output(graph, paths, aug_paths)) == NULL)
		return (NULL);
	init_lines(paths, graph);
	while (is_solution_found(paths, graph) == FALSE)
	{
		i = 0;
		while (i < graph->paths_count)
			paths->n[i++] = 0;
		paths->output_lines++;
	}
	graph->old_output_lines = paths->output_lines;
	free_tmp_paths(paths, graph);

	path = aug_paths;
	new_aug_paths = aug_paths;
	while (path != NULL)
	{
		//ft_putendl("\npath:");
		prev_paths_count = graph->paths_count;
		new_aug_paths = edmonds_disjoint_paths(graph, new_aug_paths, &path);
		if (prev_paths_count == graph->paths_count)
		{
			if ((path = get_next_path(path, graph)) == NULL)
				return (new_aug_paths);
		}
		else // start again from first path
			path = new_aug_paths;
		//sleep(1);
	}
	return (new_aug_paths);
}
