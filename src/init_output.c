/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:51:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/14 18:45:14 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	build_paths(t_graph *graph, t_paths *paths, size_t node, size_t i)
{
	t_list	*tmp;

	tmp = NULL;
	while (node != graph->sink)
	{
		if (paths->neighbours2->capacity == 0)
		{
			node = paths->neighbours2->dest;
			tmp = ft_lstnew(&node, sizeof(size_t));
			ft_lstappend(&paths->array[i], tmp);
			paths->neighbours2 = graph->nodes[node].head;
		}
		else
			paths->neighbours2 = paths->neighbours2->next;
	}
}

static void	construct_paths(t_graph *graph, t_paths *paths, size_t node)
{
	size_t	i;
	t_list	*tmp;

	tmp = NULL;
	i = 0;
	while (paths->neighbours != NULL)
	{
		if (paths->neighbours->capacity == 0)
		{
			node = paths->neighbours->dest;
			tmp = ft_lstnew(&node, sizeof(size_t));
			ft_lstappend(&paths->array[i], tmp);
			paths->neighbours2 = graph->nodes[node].head;
			build_paths(graph, paths, node, i);
			i++;
		}
		paths->neighbours = paths->neighbours->next;
	}
}

t_paths		*init_paths(t_graph *graph, t_paths *paths)
{
	t_list		*tmp;
	size_t		i;
	size_t		node;

	if ((paths = (t_paths*)malloc(sizeof(t_paths))) == NULL)
		return (NULL);
	if (!(paths->array = (t_list**)
				malloc(graph->paths_count * sizeof(t_list*))))
		return (NULL);
	i = 0;
	tmp = NULL;
	paths->neighbours = NULL;
	paths->neighbours2 = NULL;
	paths->round = 0;
	while (i < graph->paths_count)
	{
		paths->array[i] = NULL;
		tmp = ft_lstnew(&graph->source, sizeof(size_t));
		ft_lstappend(&paths->array[i], tmp);
		i++;
	}
	node = graph->source;
	paths->neighbours = graph->nodes[graph->source].head;
	construct_paths(graph, paths, node);
	return (paths);
}

t_paths		*init_output(t_graph *graph, t_paths *p)
{
	size_t		i;

	i = 0;
	if ((p = init_paths(graph, p)) == NULL)
		return (NULL);
	if ((p->ants_to_paths = (size_t*)
				malloc(graph->ants * sizeof(size_t))) == NULL)
		return (NULL);
	if ((p->n = (size_t*)malloc(graph->paths_count * sizeof(size_t))) == NULL)
		return (NULL);
	if ((p->len = (size_t*)malloc(graph->paths_count * sizeof(size_t))) == NULL)
		return (NULL);
	i = 0;
	while (i < graph->paths_count)
	{
		p->len[i] = ft_lstgetsize(p->array[i]) - 1;
		p->n[i] = 0;
		i++;
	}
	i = 0;
	while (i < graph->ants)
		p->ants_to_paths[i++] = 0;
	p->output_lines = 0;
	return (p);
}
