/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/28 18:37:21 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	update_edge_capacities(t_bfs *new_bfs, t_graph *graph,
		int8_t order)
{
	t_list	*curr;

	curr = new_bfs->shortest_path;
	while (curr->next != NULL)
	{
		if (order == INCREASE)
		{
			change_capacity(graph, curr, curr->next, DECREASE);
			change_capacity(graph, curr->next, curr, INCREASE);
		}
		else
		{
			change_capacity(graph, curr, curr->next, INCREASE);
			change_capacity(graph, curr->next, curr, DECREASE);
		}
		curr = curr->next;
	}
	ft_printf("order:%d\n", order);
	graph->paths_count += order;
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
	update_edge_capacities(new_bfs, graph, INCREASE);
	free_bfs(new_bfs);
	return (aug_paths);
}

t_list	*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_bfs	*new_bfs;
	t_paths *paths;

	if ((aug_paths = first_bfs(graph)) == NULL)
		return (NULL);
	if ((paths = init_output(graph, aug_paths)) == NULL)
		return (NULL);
	compute_output_lines(paths, graph);
	while ((new_bfs = bfs(graph)) != NULL)
	{
		ft_lstappend(&aug_paths, new_bfs->shortest_path);
		update_edge_capacities(new_bfs, graph, INCREASE);
		if (is_new_solution_better(aug_paths, graph) == FALSE)
		{
			update_edge_capacities(new_bfs, graph, DECREASE);
			ft_lstdel(&aug_paths, ft_delcontent);
			aug_paths = rebuild_aug_paths(graph);
			free_bfs(new_bfs);
			return (find_disjoint_paths(graph, aug_paths));
		}
		free_bfs(new_bfs);
	}
	return (find_disjoint_paths(graph, aug_paths));
}
