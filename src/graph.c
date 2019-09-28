/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/28 12:07:08 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t			create_edge(t_graph *graph, size_t src, size_t dest)
{
	t_edge *forward_edge;
	t_edge *backward_edge;

	if ((forward_edge = (t_edge *)malloc(sizeof(t_edge))) == NULL)
		return (FAILURE);
	forward_edge->dest = dest;
	forward_edge->capacity = 1;
	forward_edge->next = graph->array[src].head;
	graph->array[src].head = forward_edge;
	if ((backward_edge = (t_edge *)malloc(sizeof(t_edge))) == NULL)
	{
		free(forward_edge);
		return (FAILURE);
	}
	backward_edge->dest = src;
	backward_edge->next = graph->array[dest].head;
	graph->array[dest].head = backward_edge;
	return (SUCCESS);
}

static t_graph	*init_graph(t_parsing *p, t_graph *graph)
{
	size_t	i;
	t_list	*curr_nodes;
	t_list	*curr_x_coord;
	t_list	*curr_y_coord;

	i = 0;
	curr_nodes = p->nodes;
	curr_x_coord = p->x_coord;
	curr_y_coord = p->y_coord;
	while (i < graph->size)
	{
		graph->array[i].index = i;
		graph->array[i].name = ft_strdup(curr_nodes->content);
		graph->array[i].source = ((size_t)p->source == i) ? 1 : 0;
		graph->array[i].sink = ((size_t)p->sink == i) ? 1 : 0;
		graph->array[i].x_coord = *(int *)curr_x_coord->content;
		graph->array[i].y_coord = *(int *)curr_y_coord->content;
		graph->array[i].bfs_marked = 0;
		graph->array[i].head = NULL;
		curr_nodes = curr_nodes->next;
		curr_x_coord = curr_x_coord->next;
		curr_y_coord = curr_y_coord->next;
		i++;
	}
	return (graph);
}

t_graph			*create_graph(t_parsing *p)
{
	t_graph *graph;
	ssize_t	size;

	size = ft_lstgetsize(p->nodes);
	if (size == 0 || (graph = (t_graph *)malloc(sizeof(t_graph))) == NULL)
		return (NULL);
	graph->ants = p->ants;
	graph->size = size;
	if ((graph->array = (t_node *)malloc(size * sizeof(t_node))) == NULL)
	{
		free(graph);
		return (NULL);
	}
	return (init_graph(p, graph));
}
