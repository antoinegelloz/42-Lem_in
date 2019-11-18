/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:13:33 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/03 17:26:59 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	all_paths_used(t_paths *paths, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
	{
		if (paths->n[i] > 0 && paths->available[i] == TRUE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int8_t	reset_availability(t_graph *graph, t_paths *paths, size_t *capacity)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
	{
		if (capacity[i] > 0)
			paths->available[i] = TRUE;
		else
			paths->available[i] = FALSE;
		i++;
	}
	return (SUCCESS);
}

ssize_t	*save_ants_pos(t_list **ants_pos, ssize_t ants)
{
	ssize_t	*tmp_pos;
	ssize_t i;

	i = 0;
	if (!(tmp_pos = (ssize_t *)malloc(sizeof(ssize_t) * ants)))
		return (NULL);
	while (i < ants)
	{
		if (ants_pos[i] != NULL)
			tmp_pos[i] = *(ssize_t *)ants_pos[i]->content;
		else
			tmp_pos[i] = -1;
		i++;
	}
	return (tmp_pos);
}

int8_t	is_solution_found(t_paths *paths, t_graph *graph)
{
	size_t	i;
	size_t	sum;

	i = 0;
	while (i < graph->paths_count)
	{
		if (paths->output_lines < paths->len[i] - 1)
			paths->n[i] = 0;
		else if (paths->len[i] == 1)
			paths->n[i] = graph->ants;
		else
			paths->n[i] = paths->output_lines - paths->len[i] + 1;
		i++;
	}
	i = 0;
	sum = 0;
	while (i < graph->paths_count)
		sum = sum + paths->n[i++];
	if (sum >= graph->ants)
		return (TRUE);
	return (FALSE);
}

int8_t	solver(t_graph *graph, int8_t visual)
{
	t_paths	*paths;
	size_t	i;

	i = 0;
	paths = NULL;
	if ((paths = init_output(graph, paths)) == NULL)
		return (FAILURE);
	init_lines(paths, graph);
	while (is_solution_found(paths, graph) == FALSE)
	{
		i = 0;
		while (i < graph->paths_count)
			paths->n[i++] = 0;
		paths->output_lines++;
	}
	if (visual == TRUE)
		cytoscape_visualizer(graph, paths);
	flow_ants(graph, paths);
	free_paths(paths, graph);
	return (SUCCESS);
}
