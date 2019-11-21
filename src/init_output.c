/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:51:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/21 15:24:03 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*init_paths(t_graph *graph, t_paths *paths, t_list *aug_paths)
{
	t_list		*tmp;
	size_t		i;
	t_list		*curr;

	if ((paths = (t_paths*)malloc(sizeof(t_paths))) == NULL)
		return (NULL);
	if (!(paths->array = (t_list**)malloc(graph->paths_count*sizeof(t_list*))))
		return (NULL);
	i = 0;
	tmp = NULL;
	curr = aug_paths;
	while (i < graph->paths_count)
	{
		paths->array[i] = NULL;
		i++;
	}
	i = 0;
	while (curr != NULL)
	{
		tmp = ft_lstnew(curr->content, sizeof(size_t));
		ft_lstappend(&paths->array[i], tmp);
		curr = curr->next;
		if (curr != NULL && *(size_t *)curr->content == graph->source)
		{
			ft_printf("new path:\n");
			print_ssize_t(paths->array[i]);
			i++;
		}
	}
	return (paths);
}

t_paths	*init_output(t_graph *graph, t_paths *paths, t_list *aug_paths)
{	
	size_t		i;

	i = 0;
	if ((paths = init_paths(graph, paths, aug_paths)) == NULL)
		return (NULL);
	while (i < graph->paths_count)
	{
		ft_printf("path %d: ", i);
		print_ssize_t(paths->array[i]);
		i++;
	}
	if ((paths->ants_to_paths = (size_t*)malloc(graph->ants * sizeof(size_t))) == NULL)
		return (NULL);
	if ((paths->n = (size_t*)malloc(graph->paths_count * sizeof(size_t))) == NULL)
		return (NULL);
	if ((paths->len = (size_t*)malloc(graph->paths_count * sizeof(size_t))) == NULL)
		return (NULL);
	i = 0;
	while (i < graph->paths_count)
	{
		paths->len[i] = ft_lstgetsize(paths->array[i]) - 1;
		paths->n[i] = 0;
		i++;
	}
	i = 0;
	while (i < graph->ants)
		paths->ants_to_paths[i++] = 0;
	paths->output_lines = 0;
	return (paths);
}
