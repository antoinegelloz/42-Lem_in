/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:51:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/10 23:39:46 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths	*init_paths(t_graph *graph, t_paths *paths)
{
	t_list		*tmp;
	t_edge		*neighbours;
	t_edge		*neighbours2;
	size_t		i;
	size_t		node;

	if ((paths = (t_paths*)malloc(sizeof(t_paths))) == NULL)
		return (NULL);
	paths->array = (t_list**)malloc(graph->paths_count * sizeof(t_list*));
	i = 0;
	tmp = NULL;
	while (i < graph->paths_count)
	{	
		paths->array[i] = NULL;
		tmp = ft_lstnew(&graph->source, sizeof(size_t));
		ft_lstappend(&paths->array[i], tmp);
		i++;
	}
	i = 0;
	node = graph->source;
	neighbours = graph->nodes[graph->source].head;
	while (neighbours != NULL)
	{
		if (neighbours->capacity == 0)
		{
			node = neighbours->dest;
			tmp = ft_lstnew(&node, sizeof(size_t));
			ft_lstappend(&paths->array[i], tmp);
			neighbours2 = graph->nodes[node].head;
			while (node != graph->sink)
			{
				if (neighbours2->capacity == 0)
				{
					node = neighbours2->dest;
					tmp = ft_lstnew(&node, sizeof(size_t));
					ft_lstappend(&paths->array[i], tmp);
					neighbours2 = graph->nodes[node].head;
				}
				else
					neighbours2 = neighbours2->next;
			}
			i++;
		}
		neighbours = neighbours->next;
	}
	return (paths);
}

t_paths	*init_output(t_graph *graph, t_paths *paths)
{	
	size_t		i;

	i = 0;
	if ((paths = init_paths(graph, paths)) == NULL)
		return (NULL);
	while (i < graph->paths_count)
	{
		//ft_printf("path %d: ", i);
		//print_ssize_t(paths->array[i]);
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
