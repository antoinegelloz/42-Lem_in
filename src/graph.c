/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/25 15:53:58 by agelloz          ###   ########.fr       */
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
	forward_edge->next = graph->nodes[src].head;
	graph->nodes[src].head = forward_edge;
	if ((backward_edge = (t_edge *)malloc(sizeof(t_edge))) == NULL)
	{
		free(forward_edge);
		return (FAILURE);
	}
	backward_edge->dest = src;
	backward_edge->capacity = 1;
	backward_edge->next = graph->nodes[dest].head;
	graph->nodes[dest].head = backward_edge;
	return (SUCCESS);
}

static void		fill_coordinates(t_parsing *p, t_graph *graph)
{
	size_t	i;
	t_list	*curr_x_coord;
	t_list	*curr_y_coord;

	i = 0;
	curr_x_coord = p->x_coord;
	curr_y_coord = p->y_coord;
	while (i < graph->size)
	{
		graph->nodes[i].x_coord = *(int *)curr_x_coord->content;
		graph->nodes[i].y_coord = *(int *)curr_y_coord->content;
		curr_x_coord = curr_x_coord->next;
		curr_y_coord = curr_y_coord->next;
		i++;
	}
}

static t_graph	*init_graph(t_parsing *p, t_graph *graph)
{
	size_t	i;
	t_list	*curr_nodes;

	curr_nodes = p->nodes;
	i = 0;
	while (i < graph->size)
	{
		graph->nodes[i].index = i;
		graph->nodes[i].name = ft_strdup(curr_nodes->content);
		graph->nodes[i].source = ((size_t)p->source == i) ? 1 : 0;
		((size_t)p->source == i) ? graph->source = i : 1;
		graph->nodes[i].sink = ((size_t)p->sink == i) ? 1 : 0;
		((size_t)p->sink == i) ? graph->sink = i : 1;
		graph->nodes[i].bfs_marked = FALSE;
		graph->nodes[i].already_enqueued = FALSE;
		graph->nodes[i].head = NULL;
		curr_nodes = curr_nodes->next;
		i++;
	}
	fill_coordinates(p, graph);
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
	graph->paths_count = 0;
	if ((graph->nodes = (t_node *)malloc(size * sizeof(t_node))) == NULL)
	{
		free(graph);
		return (NULL);
	}
	return (init_graph(p, graph));
}
