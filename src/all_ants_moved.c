/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_ants_moved.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:11:25 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/01 21:59:25 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	count_paths_occupied(t_graph *graph,
		t_paths *paths, t_list **pos)
{
	size_t	i;
	size_t	paths_occupied;

	i = 0;
	paths_occupied = paths->paths_used;
	while (i < graph->paths_count)
	{
		if (paths->available[i] == TRUE)
			paths_occupied--;
		i++;
	}
	return (paths_occupied);
}

static int8_t	ants_launched(t_graph *graph, t_paths *paths)
{
	size_t	i;
	int8_t	all_ants_launched;

	all_ants_launched = TRUE;
	i = 0;
	while (i < graph->paths_count)
	{
		if (paths->n[i] > 0)
			all_ants_launched = FALSE;
		i++;
	}
	return (all_ants_launched);
}

int8_t			all_moved(t_list **pos, ssize_t *tmp,
		t_graph *graph, t_paths *paths)
{
	size_t	i;
	size_t	paths_occupied;
	int8_t	all_ants_launched;

	paths_occupied = count_paths_occupied(graph, paths, pos);
	all_ants_launched = ants_launched(graph, paths);
	i = 0;
	if (paths_occupied < paths->paths_used && all_ants_launched == FALSE)
	{
		ft_putcahr(' ');
		return (TRUE);
	}
	while (i < graph->ants)
	{
		if (pos[i] != NULL && *(ssize_t *)pos[i]->content == tmp[i]
				&& pos[i] != paths->array[paths->ants_to_paths[i]])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
