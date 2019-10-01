/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:51:16 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/01 18:52:32 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t			goal_achieved(int8_t *ants, t_graph *graph)
{
	int8_t		i;

	i = 0;
	while (ants[i])
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

	if ((ants = (int8_t *)ft_memalloc(graph->ants)) == NULL)
		return (FAILURE);
	while (goal_achieved(ants, graph) == FAILURE)
	{

	}
}
