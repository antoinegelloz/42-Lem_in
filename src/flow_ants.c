/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:51:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/01 19:29:53 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t			goal_achieved(int8_t *ants, t_graph *graph)
{
	int8_t		i;

	i = 0;
	while ((size_t)i < graph->ants)
	{
		if (ants[i] != graph->sink)
			return (FAILURE);	
		i++;
	}
	return (SUCCESS);
}

int8_t			flow_ants(t_graph *graph)
{
	int8_t		*ants;
	size_t		node;
	t_edge		*neighbours;
	int8_t		i;

	i = 0;
	node = graph->source;
	neighbours = graph->nodes[node].head;
	if ((ants = (int8_t *)ft_memalloc(graph->ants)) == NULL)
		return (FAILURE);
	while ((size_t)i < graph->ants)
	{
		ants[i] = node;
		//printf("ants[%d] = %d\n", i, ants[i]);
		i++;
	}
	i = 0;
	while (goal_achieved(ants, graph) == FAILURE)
	{
		while (neighbours != NULL && ants[i] != graph->sink)
		{
			if (neighbours->capacity == 0)
			{
				ants[i] = neighbours->dest;
				node = neighbours->dest;
				neighbours = graph->nodes[node].head;
				printf("L%d-%d\n", i + 1, ants[i]); 
			}
			else
				neighbours = neighbours->next;
		}
		node = graph->source;
		neighbours = graph->nodes[node].head;
		i++;
	}
	return (SUCCESS);
}
