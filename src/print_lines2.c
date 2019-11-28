/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lines2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:11:25 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 16:02:59 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	count_paths_occupied(t_graph *graph, t_paths *paths)
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

static int8_t	are_all_ants_launched(t_graph *graph, t_paths *paths)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
	{
		if (paths->n[i] > 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int8_t			all_moved(t_list **pos, ssize_t *tmp,
							t_graph *graph, t_paths *paths)
{
	size_t	i;
	size_t	paths_occupied;

	paths_occupied = count_paths_occupied(graph, paths);
	if (paths_occupied < paths->paths_used
		&& are_all_ants_launched(graph, paths) == FALSE)
	{
		ft_putchar(' ');
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
