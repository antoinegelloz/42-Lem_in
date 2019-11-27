/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/27 15:15:21 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t		update_edge_capacities(t_bfs *new_bfs, t_graph *graph, int8_t bfs_succeed)
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

t_list		*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_bfs   *new_bfs;
	t_paths *paths;
	size_t	i;

	i = 0;
	paths = NULL;
	aug_paths = NULL;
	
	if ((new_bfs = bfs(graph)) == NULL)
		return (NULL);
	ft_lstappend(&aug_paths, new_bfs->shortest_path);
	graph->paths_count++;
	update_edge_capacities(new_bfs, graph, TRUE);
	free_bfs(new_bfs);
	
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

	while (TRUE)
	{
		//ft_putendl("BFS");
		if ((new_bfs = bfs(graph)) == NULL)
			return (find_disjoint_paths(graph, aug_paths));
		ft_lstappend(&aug_paths, new_bfs->shortest_path);
		graph->paths_count++;
		update_edge_capacities(new_bfs, graph, TRUE);
		if (is_new_solution_better(aug_paths, graph) == FALSE)
		{
			graph->paths_count--;
			update_edge_capacities(new_bfs, graph, FALSE);
			ft_lstdel(&aug_paths, ft_delcontent);
			aug_paths = rebuild_aug_paths(graph);
			free_bfs(new_bfs);
			return (find_disjoint_paths(graph, aug_paths));
		}
		free_bfs(new_bfs);
	}
	return (NULL);
}
