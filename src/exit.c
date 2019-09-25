/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:00:34 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/25 17:36:22 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	exit_parsing_error(t_parsing *p)
{
	ft_lstdel(&p->rooms, ft_delcontent);
	ft_lstdel(&p->x_coord, ft_delcontent);
	ft_lstdel(&p->y_coord, ft_delcontent);
	ft_lstdel(&p->file, ft_delcontent);
	ft_putendl_fd("PARSING ERROR", 2);
	return (FAILURE);
}

void	edge_del(t_edge **edge)
{
	if (*edge)
	{
		edge_del(&(*edge)->next);
		if (edge)
		{
			free(*edge);
			*edge = NULL;
		}
	}
}

void	free_graph(t_graph *graph)
{
	size_t	index;

	index = 0;
	while (index < graph->size)
	{
		if (graph->array[index].name)
			ft_strdel(&graph->array[index].name);
		edge_del(&graph->array[index].head);
		index++;
	}
	free(graph->array);
	free(graph);
	graph = NULL;
}
