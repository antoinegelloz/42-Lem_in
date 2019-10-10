/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:13:33 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/10 23:39:37 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	all_paths_available(t_paths *paths, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
		if (paths->n[i] > 0 && paths->available[i++] == FALSE)
			return (FALSE);
	return (TRUE);
}

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
	//ft_putendl("all paths used");
	return (TRUE);
}

int8_t	reset_availability(t_paths *paths, t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
	{
		if (paths->n[i] > 0)
			paths->available[i] = TRUE;
		else
			paths->available[i] = FALSE;
		i++;
	}
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
		if (ants_pos[i] == NULL)
			i++;
		else 
		{
			if (ants_pos[i]->next == NULL)
				i++;
			else 
			{
				if (ants_pos[i]->next->next == NULL)
					i++;
				else 
					return (FALSE);
			}
		}
	}
	//ft_putendl("almost arrived");
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

ssize_t		*save_pos(t_list **ants_pos, ssize_t ants)
{
	ssize_t	*tmp_pos;
	ssize_t i;

	i = 0;
	if ((tmp_pos = (ssize_t *)malloc(sizeof(ssize_t) * ants)) == NULL)
		return (NULL);
	while (i < ants)
	{	
		if (ants_pos[i] != NULL)
			tmp_pos[i] = *(ssize_t *)ants_pos[i]->content;
		else
			tmp_pos[i] = -1;
		//ft_printf("tmp_pos[%d] = %d\n", i, tmp_pos[i]);
		i++;
	}
	return (tmp_pos);
}

int8_t	all_ants_moved(t_list **ants_pos, ssize_t *tmp_pos, t_graph *graph, t_paths *paths, size_t paths_used, size_t ant)
{
	size_t	i;
	size_t	paths_occupied;
	int8_t	all_ants_launched;

	i = 0;
	paths_occupied = 0;
	while (i < graph->ants)
	{
		if (ants_pos[i] == paths->array[paths->ants_to_paths[i]]->next && ants_pos[i]->next->next != NULL)
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
	if (paths_occupied < paths_used && all_ants_launched == FALSE)
	{
		if (ants_pos[ant] != NULL)
		{
			//ft_printf("|pos[%d]=%d|", ant, *(size_t *)ants_pos[ant]->content);
			//if (*(size_t *)ants_pos[ant]->content > 0 && ants_pos[ant] != paths->array[graph->paths_count - 1]->next)
			if (*(size_t *)ants_pos[ant]->content != graph->source)
				ft_putstr(" ");
		}
		else
			ft_putstr(" ");
		return (TRUE);
	}
	i = 0;
	while (i < graph->ants)
	{
		if (ants_pos[i] != NULL && *(ssize_t *)ants_pos[i]->content == tmp_pos[i] && ants_pos[i] != paths->array[paths->ants_to_paths[i]])
			return (FALSE);
		i++;
	}
	//ft_putendl("all ants moved");
	return (TRUE);
}

int8_t	all_possible_movements_finished(t_list **ants_pos, t_paths *paths, t_graph *graph, size_t ant)
{
	while (ant < graph->ants)
	{
		if (ants_pos[ant] == paths->array[paths->ants_to_paths[ant]] && paths->available[paths->ants_to_paths[ant]] == TRUE)
			return (FALSE);
		if (ants_pos[ant] != NULL)
			return (FALSE);
		ant++;
	}
	return (TRUE);
}

int8_t	print_lines(t_paths *paths, t_graph *graph, size_t paths_used)
{
	t_list	**ants_pos;
	ssize_t	*tmp_pos;
	size_t	ant;
	size_t	round;
	size_t	j;
	int8_t	almost_arrived;

	almost_arrived = FALSE;
	if ((ants_pos = (t_list **)malloc(sizeof(t_list *) * graph->ants)) == NULL)
		return (FAILURE);
	ant = 0;
	//ft_printf("output=%d ants:%d\n\n", paths->output_lines, graph->ants);
	while (ant < graph->ants)
	{	
		ants_pos[ant] = paths->array[paths->ants_to_paths[ant]];
		ant++;
	}
	round = 0;
	while (round < paths->output_lines)
	{
		tmp_pos = save_pos(ants_pos, graph->ants);
		ant = 0;
		while (ant < graph->ants)
		{
			j = 0;
			if (ants_pos[ant] == paths->array[paths->ants_to_paths[ant]])
			{
				if (paths->available[paths->ants_to_paths[ant]] == TRUE)
				{
					ants_pos[ant] = ants_pos[ant]->next;
					if (ants_pos[ant] != NULL)
					{
						if (ants_pos[ant]->next != NULL)
						{
							paths->available[paths->ants_to_paths[ant]] = FALSE;
							paths->n[paths->ants_to_paths[ant]]--;
						}
					}
					ft_printf("L%d-%s", ant + 1, graph->nodes[*(size_t *)ants_pos[ant]->content].name);
				}
			}
			else if (ants_pos[ant] != NULL)
			{
				if (ants_pos[ant]->next != NULL)
				{
					if (ants_pos[ant] == paths->array[paths->ants_to_paths[ant]]->next && paths->n[paths->ants_to_paths[ant]] > 0)
						paths->available[paths->ants_to_paths[ant]] = TRUE;
					ants_pos[ant] = ants_pos[ant]->next;
					if (ants_pos[ant] != NULL)
						ft_printf("L%d-%s", ant + 1, graph->nodes[*(size_t *)ants_pos[ant]->content].name);
				}
				else if (ants_pos[ant]->next == NULL)
					ants_pos[ant] = ants_pos[ant]->next;
			}
			//if (ants_pos[ant] != NULL)
			//ft_printf("|ants_pos[%d]=%d|", ant, *(size_t *)ants_pos[ant]->content);
			if (ant < graph->ants)
			{
				if (ants_pos[ant] != NULL)
				{
					if (ants_pos[ant]->next == NULL)
						ants_pos[ant] = ants_pos[ant]->next;
					if (all_ants_moved(ants_pos, tmp_pos, graph, paths, paths_used, ant) == FALSE)
						ft_putchar(' ');
				}
			}
			ant++;
		}
		ft_putchar('\n');
		round++;
	}
	return (SUCCESS);
}

int8_t	flow_ants(t_graph *graph, t_paths *paths) 
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	paths_used;
	size_t	tmp[graph->paths_count];

	i = 0;
	paths_used = 0;
	while (i < graph->paths_count)
	{
		//ft_printf("n[%d] = %d\n", i, paths->n[i]);
		if (paths->n[i] > 0)
			paths_used++;
		tmp[i] = paths->n[i];
		i++;
	}
	//ft_printf("paths_used = %d\n", paths_used);
	paths->available = (int8_t *)malloc(sizeof(int8_t) * graph->paths_count);
	reset_availability(paths, graph);
	i = 0;
	while (i < graph->ants)
	{
		j = 0;
		if (all_paths_used(paths, graph) == TRUE)
		{
			//ft_putendl("reset1");
			k = 0;
			while (k < graph->paths_count)
			{
				if (tmp[k] > 0)
					paths->available[k] = TRUE;
				else
					paths->available[k] = FALSE;
				k++;
			}
			reset_availability(paths, graph);
		}
		while (j < graph->paths_count)
		{
			//ft_printf("paths->available[%d]=%d tmp[%d]=%d paths->n[%d] = %d\n", j, paths->available[j], j, tmp[j], j, paths->n[j]);

			if (tmp[j] == 0)
				paths->available[j] = FALSE;
			if (paths->available[j] == TRUE && tmp[j] > 0)
			{
				//ft_putendl("set");
				paths->ants_to_paths[i] = j;
				//ft_printf("ants_to_paths[%d] = %d\n", i, paths->ants_to_paths[i]);
				tmp[j]--;
				paths->available[j] = FALSE;
				break ;
			}
			if (j == graph->paths_count - 1 && paths->available[j] == FALSE)
			{
				k = 0;
				while (k < graph->paths_count)
				{
					if (tmp[k] > 0)
						paths->available[k] = TRUE;
					else
						paths->available[k] = FALSE;
					k++;
				}
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
		//ft_printf("n[%d] = %d\n", i, paths->n[i]);
		i++;
	}
	reset_availability(paths, graph);
	print_lines(paths, graph, paths_used);
	return (SUCCESS);
}

int8_t	is_solution_found(t_paths *paths, t_graph *graph)
{
	size_t	i;
	size_t	sum;

	i = 0;
	while (i < graph->paths_count)
	{
		//ft_printf("output=%d len[%d]=%d\n", paths->output_lines, i, paths->len[i]);
		if (paths->output_lines < paths->len[i] - 1) 
			paths->n[i] = 0;
		else if (paths->len[i] == 1)
			paths->n[i] = graph->ants;
		else
			paths->n[i] = paths->output_lines - paths->len[i] + 1;
		//ft_printf("paths->n[%d]=%d\n", i, paths->n[i]);
		i++;
	}
	i = 0;
	sum = 0;
	while (i < graph->paths_count)
	{
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
	//ft_printf("paths_count=%d\n", graph->paths_count);
	while (is_solution_found(paths, graph) == FALSE)
	{
		reset_n(paths, graph);
		paths->output_lines++;
	}
	//ft_printf("output=%d\n", paths->output_lines);
	flow_ants(graph, paths);
	return (SUCCESS);
}
