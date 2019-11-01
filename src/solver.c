/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:13:33 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/31 17:13:39 by agelloz          ###   ########.fr       */
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

int8_t	init_lines(t_paths *paths, t_graph *graph)
{
	size_t	i;
	size_t	tmp;

	paths->output_lines = ft_lstgetsize(paths->array[0]) - 1;
	i = 1;
	while (i < graph->paths_count)
	{
		tmp = ft_lstgetsize(paths->array[i]) - 1;
		if (tmp < paths->output_lines)
			paths->output_lines = tmp;
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

int8_t	all_moved(t_list **pos, ssize_t *tmp, t_graph *graph, t_paths *paths)
{
	size_t	i;
	size_t	paths_occupied;
	int8_t	all_ants_launched;

	i = 0;
	paths_occupied = 0;
	while (i < graph->ants)
	{
		if (pos[i] == paths->array[paths->ants_to_paths[i]]->next
			&& pos[i]->next->next != NULL)
			paths_occupied++;
		i++;
	}
	all_ants_launched = TRUE;
	i = 0;
	while (i < graph->paths_count)
	{
		if (paths->n[i] > 0)
			all_ants_launched = FALSE;
		i++;
	}
	//ft_printf("|occ:%d all=%d|", paths_occupied, all_ants_launched);
	if (paths_occupied < paths->paths_used && all_ants_launched == FALSE)
	{
		ft_putstr(" ");
		return (TRUE);
	}
	i = 0;
	while (i < graph->ants)
	{
		if (pos[i] != NULL && *(ssize_t *)pos[i]->content == tmp[i]
			&& pos[i] != paths->array[paths->ants_to_paths[i]])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int8_t	print_lines(t_paths *paths, t_graph *graph)
{
	t_list	**ants_pos;
	ssize_t	*tmp_pos;
	size_t	round;
	size_t	i;

	if ((ants_pos = (t_list**)malloc(sizeof(t_list*)*graph->ants)) == NULL)
		return (FAILURE);
	i = 0;
	while (i < graph->paths_count)
	{
		//ft_printf("path %d: ", i);
		//print_ssize_t(paths->array[i]);
		i++;
	}
	//ft_printf("paths_count=%d paths_used=%d output=%d ants:%d\n\n", graph->paths_count, paths->paths_used, paths->output_lines, graph->ants);
	i = 0;
	while (i < graph->ants)
	{
		ants_pos[i] = paths->array[paths->ants_to_paths[i]];
		i++;
	}
	round = 0;
	while (round < paths->output_lines)
	{
		if (!(tmp_pos = save_ants_pos(ants_pos, graph->ants)))
				return (FAILURE);
		i = 0;
		while (i < graph->ants)
		{
			if (ants_pos[i] == paths->array[paths->ants_to_paths[i]])
			{
				if (paths->available[paths->ants_to_paths[i]] == TRUE)
				{
					ants_pos[i] = ants_pos[i]->next;
					if (ants_pos[i] != NULL && ants_pos[i]->next != NULL)
					{
						paths->available[paths->ants_to_paths[i]] = FALSE;
						paths->n[paths->ants_to_paths[i]]--;
					}
					ft_printf("L%d-%s", i + 1, graph->nodes[*(size_t *)ants_pos[i]->content].name);
				}
			}
			else if (ants_pos[i] != NULL && ants_pos[i]->next != NULL)
			{
				if (ants_pos[i] == paths->array[paths->ants_to_paths[i]]->next && paths->n[paths->ants_to_paths[i]] > 0)
					paths->available[paths->ants_to_paths[i]] = TRUE;
				ants_pos[i] = ants_pos[i]->next;
				if (ants_pos[i] != NULL)
					ft_printf("L%d-%s", i + 1, graph->nodes[*(size_t *)ants_pos[i]->content].name);
			}
			else if (ants_pos[i] != NULL && ants_pos[i]->next == NULL)
				ants_pos[i] = ants_pos[i]->next;
			if (i < graph->ants && ants_pos[i] != NULL)
			{
				if (ants_pos[i]->next == NULL)
					ants_pos[i] = ants_pos[i]->next;
				if (all_moved(ants_pos, tmp_pos, graph, paths) == FALSE)
					ft_putchar(' ');
			}
			i++;
		}
		ft_putchar('\n');
		free(tmp_pos);
		tmp_pos = NULL;
		round++;
	}
	free(ants_pos);
	ants_pos = NULL;
	return (SUCCESS);
}

int8_t	flow_ants(t_graph *graph, t_paths *paths) 
{
	size_t	i;
	size_t	j;
	size_t	tmp[graph->paths_count];

	i = 0;
	paths->paths_used = 0;
	while (i < graph->paths_count)
	{
		//ft_printf("init n[%d] = %d\n", i, paths->n[i]);
		if (paths->n[i] > 0)
			paths->paths_used++;
		tmp[i] = paths->n[i];
		i++;
	}
	if (!(paths->available = (int8_t*)malloc(sizeof(int8_t)*graph->paths_count)))
		return (FAILURE);
	reset_availability(graph, paths, paths->n);
	i = 0;
	while (i < graph->ants)
	{
		j = 0;
		if (all_paths_used(paths, graph) == TRUE)
			reset_availability(graph, paths, tmp);
		while (j < graph->paths_count)
		{
			//ft_printf("paths->available[%d]=%d tmp[%d]=%d paths->n[%d] = %d\n", j, paths->available[j], j, tmp[j], j, paths->n[j]);
			if (tmp[j] == 0)
				paths->available[j] = FALSE;
			if (paths->available[j] == TRUE && tmp[j] > 0)
			{
				paths->ants_to_paths[i] = j;
				//ft_printf("ants_to_paths[%d] = %d\n", i, paths->ants_to_paths[i]);
				tmp[j]--;
				paths->available[j] = FALSE;
				break ;
			}
			if (j == graph->paths_count - 1 && paths->available[j] == FALSE)
			{
				reset_availability(graph, paths, tmp);
				j = 0;
			}
			else
				j++;
		}
		i++;
	}
	i = 0;
	while (i < graph->paths_count)
	{
		paths->n[i] = paths->n[i] - tmp[i];
		//ft_printf("final n[%d] = %d\n", i, paths->n[i]);
		i++;
	}
	reset_availability(graph, paths, paths->n);
	print_lines(paths, graph);
	return (SUCCESS);
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
	flow_ants(graph, paths);
	if (visual == TRUE)
		cytoscape_visualizer(graph, paths);
	free_paths(paths, graph);
	return (SUCCESS);
}
