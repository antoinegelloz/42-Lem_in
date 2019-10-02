/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:51:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/02 10:19:20 by agelloz          ###   ########.fr       */
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

int8_t	flow_ants(t_graph *graph)
{
	size_t		*ants;
	size_t		node;
	size_t		i;
	t_edge		*neighbours;

	i = 0;
	node = graph->source;
	neighbours = graph->nodes[node].head;
	if ((ants = (size_t *)ft_memalloc(graph->ants)) == NULL)
		return (FAILURE);
	while (i < graph->ants)
		ants[i++] = node;
	i = 0;
	while (goal_achieved(ants, graph) == FALSE)
	{
		while (neighbours != NULL && ants[i] != graph->sink)
		{
			if (neighbours->capacity == 0)
			{
				ants[i] = neighbours->dest;
				node = neighbours->dest;
				neighbours = graph->nodes[node].head;
				printf("L%zd-%zd\n", i + 1, ants[i]); 
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
