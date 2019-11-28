/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:51:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 23:32:32 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*init_paths(t_graph *graph, t_list *aug_paths)
{
	t_list		*tmp;
	size_t		i;
	t_list		*curr;
	t_paths		*paths;

	if (!(paths = malloc(sizeof(t_paths))))
		return (NULL);
	if (!(paths->array = malloc(graph->paths_count * sizeof(t_list*))))
		return (free_paths(paths, graph));
	i = 0;
	while (i < graph->paths_count)
		paths->array[i++] = NULL;
	i = 0;
	curr = aug_paths;
	while (curr != NULL)
	{
		tmp = ft_lstnew(curr->content, sizeof(size_t));
		ft_lstappend(&paths->array[i], tmp);
		curr = curr->next;
		if (curr != NULL && *(size_t *)curr->content == graph->source)
			i++;
	}
	return (paths);
}

t_paths	*init_output(t_graph *graph, t_list *aug_paths)
{
	t_paths	*paths;
	size_t	i;

	if (!(paths = init_paths(graph, aug_paths)))
		return (free_paths(paths, graph));
	if (!(paths->ants_to_paths = malloc(graph->ants * sizeof(size_t))))
		return (free_paths(paths, graph));
	if (graph->paths_count)
	{
		if (!(paths->n = malloc(graph->paths_count * sizeof(size_t))))
			return (free_paths(paths, graph));
		if (!(paths->len = malloc(graph->paths_count * sizeof(size_t))))
			return (free_paths(paths, graph));
	}
	i = 0;
	while (i < graph->paths_count)
	{
		paths->len[i] = ft_lstgetsize(paths->array[i]) - 1;
		paths->n[i++] = 0;
	}
	i = 0;
	while (i < graph->ants)
		paths->ants_to_paths[i++] = 0;
	paths->output_lines = 0;
	return (paths);
}
