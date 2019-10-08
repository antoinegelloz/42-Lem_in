/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:13:33 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/08 12:12:28 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	all_paths_used(t_paths *paths, size_t paths_used)
{
	size_t	i;

	i = 0;
	while (i < paths_used)
		if (paths->available[i++] == 1)
			return (FALSE);
	return (TRUE);
}

int8_t	reset_availability(t_paths *paths, size_t paths_used)
{
	size_t	i;

	i = 0;
	while (i < paths_used)
		paths->available[i++] = 1;
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

int8_t	print_lines(size_t paths_used, t_paths *paths, t_graph *graph)
{
	t_list	**ants_pos;
	size_t	ant;
	size_t	round;

	if ((ants_pos = (t_list **)malloc(sizeof(t_list *) * graph->ants)) == NULL)
		return (FAILURE);
	ant = 0;
	while (ant < graph->ants)
	{	
		ants_pos[ant] = paths->array[paths->ants_to_paths[ant]]->next;
		ant++;
	}
	round = 0;
	ft_printf("output_lines:%d\n\n", paths->output_lines);
	while (round < paths->output_lines)
	{
		//ft_printf("--round:%d\n", round);
		ant = 0;
		while (ant < graph->ants)
		{
			if (ants_pos[ant] != NULL)
			{
				//ft_printf("ant:%d node:%d\n", ant, *(size_t *)ants_pos[ant]->content);
				ft_printf("L%d-%s ", ant + 1, graph->nodes[*(size_t *)ants_pos[ant]->content].name);
				//ft_printf("paths[%d]\n", paths->ants_to_paths[ant]);
				//ft_printf("paths->available[%d]\n", *(size_t *)paths->array[paths->ants_to_paths[ant]]->content);
				//ft_printf("ants_pos[%d] = %d paths->array[%d]->next = %d\n", ant, *(size_t *)ants_pos[ant]->content, paths->ants_to_paths[ant], *(size_t *)paths->array[paths->ants_to_paths[ant]]->next->content);
				if (*(size_t *)ants_pos[ant]->content == *(size_t *)paths->array[paths->ants_to_paths[ant]]->next->content)
				{
					//ft_putendl("available false");
					paths->available[paths->ants_to_paths[ant]] = FALSE;
				}
				ants_pos[ant] = ants_pos[ant]->next;
			}
			//ft_printf("ants_to_path:%d last_path_used:%d\n", paths->ants_to_paths[ant], last_path_used);
			if (all_paths_used(paths, paths_used) == TRUE)
			{
				//ft_putendl("break");
				reset_availability(paths, paths_used);
				ft_putchar('\n');
				break ;
			}
			ant++;
		}
		round++;
	}
	ft_putchar('\n');
	return (SUCCESS);
}

int8_t	flow_ants(t_graph *graph, t_paths *paths)
{
	size_t	i;
	size_t	j;
	size_t	paths_used;

	i = 0;
	paths_used = 0;
	while (i < graph->paths_count)
	{
		ft_printf("n[%d] = %d\n", paths_used, paths->n[paths_used]);
		if (paths->n[paths_used] != 0)
			paths_used++;
		i++;
	}
	paths->available = (int8_t *)malloc(sizeof(int8_t) * paths_used);
	i = 0;
	while (i < paths_used)
		paths->available[i++] = TRUE;
	i = 0;
	while (i < graph->ants)
	{
		j = 0;
		if (all_paths_used(paths, paths_used) == TRUE)
			reset_availability(paths, paths_used);
		while (j < paths_used)
		{
			if (paths->available[j] == TRUE && paths->n[j] > 0)
			{
				paths->ants_to_paths[i] = j;
				ft_printf("ants_to_paths[%d] = %d\n", i, paths->ants_to_paths[i]);
				paths->n[j]--;
				paths->available[j] = FALSE;
				break;
			}
			j++;
		}
		i++;
	}
	reset_availability(paths, paths_used);
	print_lines(paths_used, paths, graph);
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
		else
			paths->n[i] = paths->output_lines - paths->len[i] + 1;
		i++;
	}
	i = 0;
	sum = 0;
	while (i < graph->paths_count)
	{
		sum = sum + paths->n[i];
		i++;
	}
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
