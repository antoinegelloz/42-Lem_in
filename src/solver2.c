/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:15:53 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 16:37:27 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		update_n(t_graph *graph, t_paths *paths, size_t tmp[])
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
	{
		paths->n[i] = paths->n[i] - tmp[i];
		i++;
	}
	reset_availability(graph, paths, paths->n);
}

static size_t	update_index(t_graph *graph, t_paths *paths, size_t tmp[],
								size_t j)
{
	if (j == graph->paths_count - 1 && paths->available[j] == FALSE)
	{
		reset_availability(graph, paths, tmp);
		j = 0;
	}
	else
		j++;
	return (j);
}

static void		all_paths_used(t_graph *graph, t_paths *paths, size_t tmp[])
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
	{
		if (paths->n[i] > 0 && paths->available[i] == TRUE)
			return ;
		i++;
	}
	reset_availability(graph, paths, tmp);
}

static void		assign_ants_to_paths(t_graph *graph, t_paths *paths,
								size_t tmp[])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < graph->ants)
	{
		all_paths_used(graph, paths, tmp);
		j = 0;
		while (j < graph->paths_count)
		{
			if (tmp[j] == 0)
				paths->available[j] = FALSE;
			if (paths->available[j] == TRUE && tmp[j] > 0)
			{
				paths->ants_to_paths[i] = j;
				tmp[j]--;
				paths->available[j] = FALSE;
				break ;
			}
			j = update_index(graph, paths, tmp, j);
		}
		i++;
	}
	update_n(graph, paths, tmp);
}

int8_t			solver2(t_graph *graph, t_paths *paths, t_options *o)
{
	size_t	i;
	size_t	tmp[graph->paths_count];

	i = 0;
	paths->paths_used = 0;
	while (i < graph->paths_count)
	{
		if (paths->n[i] > 0)
			paths->paths_used++;
		tmp[i] = paths->n[i];
		i++;
	}
	if (!(paths->available = (int8_t*)malloc(sizeof(int8_t)
											* graph->paths_count)))
		return (FAILURE);
	reset_availability(graph, paths, paths->n);
	assign_ants_to_paths(graph, paths, tmp);
	if (o->visual == TRUE)
		visualizer(graph, paths);
	print_lines(paths, graph);
	return (SUCCESS);
}
