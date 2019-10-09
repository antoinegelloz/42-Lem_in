/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:13:33 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/09 17:09:59 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	all_paths_available(t_paths *paths, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
		if (paths->available[i++] == 0)
			return (FALSE);
	return (TRUE);
}

int8_t	all_paths_used(t_paths *paths, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
		if (paths->available[i++] == 1)
			return (FALSE);
	return (TRUE);
}

int8_t	reset_availability(t_paths *paths, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
		paths->available[i++] = 1;
	return (SUCCESS);
}

int8_t	all_ants_arrived(t_list	**ants_pos, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->ants)
	{
		if (ants_pos[i] != NULL)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int8_t	all_ants_almost_arrived(t_list	**ants_pos, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->ants)
	{
		if (ants_pos[i] != NULL) 
			if (ants_pos[i]->next != NULL)
				return (FALSE);
		i++;
	}
	return (TRUE);
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

int8_t	print_lines(size_t paths_used, t_paths *paths, t_graph *graph)
{
	t_list	**ants_pos;
	size_t	ant;
	size_t	round;
	size_t	j;

	if ((ants_pos = (t_list **)malloc(sizeof(t_list *) * graph->ants)) == NULL)
		return (FAILURE);
	ant = 0;
	while (ant < graph->ants)
	{	
		ants_pos[ant] = paths->array[paths->ants_to_paths[ant]];
		ant++;
	}
	round = 0;
	//ft_printf("output_lines:%d\n\n", paths->output_lines);
	while (all_ants_arrived(ants_pos, graph) == FALSE)
	{
		ant = 0;
		while (ant < graph->ants)
		{
			j = 0;
			if (ants_pos[ant] == paths->array[paths->ants_to_paths[ant]])
			{
				//ft_printf("-ants_to_paths[%d] = %d\n", ant, paths->ants_to_paths[ant]);
				if (paths->available[paths->ants_to_paths[ant]] == TRUE)
				{
					ants_pos[ant] = ants_pos[ant]->next;
					ft_printf("L%d-%s", ant + 1, graph->nodes[*(size_t *)ants_pos[ant]->content].name);
					if (ants_pos[ant]->next != NULL)
						paths->available[paths->ants_to_paths[ant]] = FALSE;
					if (ant == graph->ants - 1)
						ft_putchar('\n');
					else
						ft_putchar(' ');
				}
				else
				{
					ft_putchar('\n');
					break ;
				}
			}
			else if (ants_pos[ant] != NULL)
			{
				if (ants_pos[ant]->next != NULL)
				{
					if (ants_pos[ant] == paths->array[paths->ants_to_paths[ant]]->next)
						paths->available[paths->ants_to_paths[ant]] = TRUE;
					ants_pos[ant] = ants_pos[ant]->next;
					if (ants_pos[ant] != NULL)
						ft_printf("L%d-%s", ant + 1, graph->nodes[*(size_t *)ants_pos[ant]->content].name);
					if ((ant == graph->ants - 1 && ants_pos[ant] != NULL) || all_ants_almost_arrived(ants_pos, graph) == TRUE)
						ft_putchar('\n');
					else if (ants_pos[ant] != NULL)
						ft_putchar(' ');
				}
				else if (ants_pos[ant]->next == NULL)
					ants_pos[ant] = ants_pos[ant]->next;
			}
			ant++;
		}
	}
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
		//ft_printf("n[%d] = %d\n", i, paths->n[i]);
		if (paths->n[i] != 0)
			paths_used++;
		i++;
	}
	//printf("paths_used = %zd\n", paths_used);
	paths->available = (int8_t *)malloc(sizeof(int8_t) * graph->paths_count);
	i = 0;
	while (i < graph->paths_count)
		paths->available[i++] = TRUE;
	i = 0;
	while (i < graph->ants)
	{
		j = 0;
		if (all_paths_used(paths, graph) == TRUE)
			reset_availability(paths, graph);
		while (j < graph->paths_count)
		{
			//printf("paths->n[%zd]\n", j);
			if (j == graph->paths_count)
				break ;
			//printf("paths->available[%zd] = %d & paths->n[%zd] = %zd\n", j, paths->available[j], j, paths->n[j]);
			if (paths->n[j] == 0)
				paths->available[j] = FALSE;
			if (paths->available[j] == TRUE && paths->n[j] > 0)
			{
				paths->ants_to_paths[i] = j;
				//ft_printf("ants_to_paths[%d] = %d\n", i, paths->ants_to_paths[i]);
				paths->n[j]--;
				paths->available[j] = FALSE;
				if (i == graph->ants - 1)
				{
					i++;
					break ;
				}
				i++;
			//	break ;
			}	
			j++;
		}
		//i++;
		//sleep(1);
		if (i == graph->ants)
			break;
	}
	reset_availability(paths, graph);
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
		//ft_printf("paths->n[%d]=%d\n", i, paths->n[i]);
		sum = sum + paths->n[i];
		i++;
	}
	//ft_printf("sum=%d\n", sum);
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
	//ft_printf("output=%d\n", paths->output_lines);
	flow_ants(graph, paths);
	return (SUCCESS);
}
