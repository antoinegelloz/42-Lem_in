/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:51:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/07 18:02:57 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	goal_achieved(size_t *ants, t_graph *graph)
{
	size_t		i;

	i = 0;
	while (i < graph->ants)
		if (ants[i++] != graph->sink)
			return (FALSE);	
	return (TRUE);
}

t_paths	*init_paths(t_graph *graph)
{
	t_paths		*paths;
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

int8_t	flow_ants(t_graph *graph)
{	
	size_t		i;
	t_paths		*paths;

	i = 0;
	if ((paths = init_paths(graph)) == NULL)
		return (FAILURE);
	while (i < graph->paths_count)
	{
		printf("Path %zd :\n", i);
		print_ssize_t(paths->array[i]);
		i++;
	}	
	return (SUCCESS);
}
