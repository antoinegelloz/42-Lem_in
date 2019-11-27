/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/27 17:57:47 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	update_edge_capacities(t_bfs *new_bfs, t_graph *graph,
		int8_t bfs_succeed)
{
	t_list	*curr;

	curr = NULL;
	curr = new_bfs->shortest_path;
	while (curr->next != NULL)
	{
		if (bfs_succeed == TRUE)
		{
			change_capacity(graph, curr, curr->next, DECREASE);
			change_capacity(graph, curr->next, curr, INCREASE);
			curr = curr->next;
		}
		else
		{
			change_capacity(graph, curr, curr->next, INCREASE);
			change_capacity(graph, curr->next, curr, DECREASE);
			curr = curr->next;
		}
	}
	return (SUCCESS);
}

void	compute_output_lines(t_paths *paths, t_graph *graph)
{
	size_t	i;

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
}

t_list	*first_bfs(t_graph *graph)
{
	t_list	*aug_paths;
	t_bfs	*new_bfs;

	aug_paths = NULL;
	if ((new_bfs = bfs(graph)) == NULL)
		return (NULL);
	ft_lstappend(&aug_paths, new_bfs->shortest_path);
	graph->paths_count++;
	update_edge_capacities(new_bfs, graph, TRUE);
	free_bfs(new_bfs);
	return (aug_paths);
}

void	update_data(t_graph *graph, t_bfs *new_bfs, int8_t bfs_succeed)
{
	if (bfs_succeed == TRUE)
	{
		graph->paths_count++;
		update_edge_capacities(new_bfs, graph, bfs_succeed);
	}
	else
	{
		graph->paths_count--;
		update_edge_capacities(new_bfs, graph, bfs_succeed);
	}
}

t_list	*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_bfs	*new_bfs;
	t_paths *paths;

	paths = NULL;
	if ((aug_paths = first_bfs(graph)) == NULL)
		return (NULL);
	if ((paths = init_output(graph, paths, aug_paths)) == NULL)
		return (NULL);
	compute_output_lines(paths, graph);
	while ((new_bfs = bfs(graph)) != NULL)
	{
		ft_lstappend(&aug_paths, new_bfs->shortest_path);
		update_data(graph, new_bfs, TRUE);
		if (is_new_solution_better(aug_paths, graph) == FALSE)
		{
			update_data(graph, new_bfs, FALSE);
			ft_lstdel(&aug_paths, ft_delcontent);
			aug_paths = rebuild_aug_paths(graph);
			free_bfs(new_bfs);
			return (find_disjoint_paths(graph, aug_paths));
		}
		free_bfs(new_bfs);
	}
	return (find_disjoint_paths(graph, aug_paths));
}
