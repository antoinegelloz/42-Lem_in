/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:13:33 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/07 22:01:51 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	print_lines(size_t last_path_used, t_paths *paths, t_graph *graph)
{
	t_list	**ants_pos;
	size_t	ant;
	size_t	round;

	if ((ants_pos = (t_list **)malloc(sizeof(t_list *) * graph->ants)) == NULL)
		return (FAILURE);
	ant = 0;
	while (ant < graph->ants)
	{	
		ants_pos[ant] = paths->array[paths->ants_to_paths[ant]];
		ant++;
	}
	round = 0;
	ft_printf("output_lines:%d\n", paths->output_lines);
	while (round < paths->output_lines)
	{
		ant = 0;
		while (ant < graph->ants)
		{
			if (ants_pos[ant] != NULL)
			{
				ft_printf("L%d-%s ", ant, graph->nodes[*(size_t *)ants_pos[ant]->content].name);
				ants_pos[ant] = ants_pos[ant]->next;
			}
			if (paths->ants_to_paths[ant] == last_path_used)
			{
				ft_putchar('\n');
				break ;
			}
			ant++;
		}
		round++;
	}
	return (SUCCESS);
}

int8_t	all_paths_used(int8_t *paths_available, size_t paths_used)
{
	size_t	i;

	i = 0;
	while (i < paths_used)
	{
		if (paths_available[i] == 1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int8_t	reset_availability(int8_t *paths_available, size_t paths_used)
{
	size_t	i;

	i = 0;
	while (i < paths_used)
		paths_available[i++] = 1;
	return (SUCCESS);
}

int8_t	flow_ants(t_graph *graph, t_paths *paths)
{
	int8_t	*paths_available;
	size_t	i;
	size_t	j;
	size_t	paths_used;
	size_t	last_path_used;

	i = 0;
	paths_used = 0;
	last_path_used = 0;
	while (i < graph->paths_count)
	{
		if (paths->n[paths_used] != 0)
		{
			last_path_used = i;
			paths_used++;
		}
		i++;
	}
	paths_available = (int8_t *)malloc(sizeof(int8_t) * paths_used);
	i = 0;
	while (i < paths_used)
		paths_available[i++] = TRUE;
	i = 0;
	while (i < graph->ants)
	{
		j = 0;
		if (all_paths_used(paths_available, paths_used) == TRUE)
			reset_availability(paths_available, paths_used);
		while (j < paths_used)
		{
			if (paths_available[j] == TRUE && paths->n[j] > 0)
			{
				paths->ants_to_paths[i] = j;
				paths->n[j]--;
				paths_available[j] = 0;
				break;
			}
			j++;
		}
		i++;
	}
	print_lines(last_path_used, paths, graph);
	return (SUCCESS);
}

int8_t	reset_n(t_paths *paths, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
		paths->n[i++] = 0;
	return (SUCCESS);
}

int8_t	init_lines(t_paths *paths, t_graph *graph)
{
	size_t	i;
	size_t	tmp;

	paths->output_lines = ft_lstgetsize(paths->array[0]);
	i = 1;
	while (i < graph->paths_count)
	{
		tmp = ft_lstgetsize(paths->array[i]);
		if (tmp < paths->output_lines)
			paths->output_lines = tmp;
		i++;
	}
	return (SUCCESS);
}

int8_t	is_solution_found(t_paths *paths, t_graph *graph)
{
	size_t	i;
	size_t	sum;

	i = 0;
	while (i < graph->paths_count)
	{
		if (paths->output_lines > paths->len[i] - 1) 
			paths->n[i] = 0;
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

int8_t	solver(t_graph *graph)
{
	t_paths	*paths;

	paths = NULL;
	if ((paths = init_output(graph, paths)) == NULL)
		return (FAILURE);
	init_lines(paths, graph);
	while (is_solution_found(paths, graph) == FALSE)
	{
		reset_n(paths, graph);
		paths->output_lines++;
	}
	flow_ants(graph, paths);
	return (SUCCESS);
}
