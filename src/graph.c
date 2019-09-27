/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/27 14:07:10 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_graph(t_graph *graph)
{
	size_t	i;
	t_edge	*temp;

	if (graph == NULL)
		return ;
	ft_putendl("\nGraph:");
	i = 0;
	while (i < graph->size)
	{
		temp = graph->array[i].head;
		ft_printf("Node|%d|, Name|%s|, x|%d|, y|%d|", i, graph->array[i].name, graph->array[i].x_coord, graph->array[i].y_coord);
		while (temp)
		{
			ft_printf(" -> %d", temp->dest);
			temp = temp->next;
		}
		ft_printf("\n");
		i++;
	}
}

int8_t	create_edge(t_graph *graph, size_t src, size_t dest)
{
	t_edge *forward_edge;
	t_edge *backward_edge;

	if ((forward_edge = (t_edge *)malloc(sizeof(t_edge))) == NULL)
		return (FAILURE);
	forward_edge->dest = dest;
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

t_graph	*create_graph(t_parsing *p)
{
	t_graph *graph;
	ssize_t i;
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
	i = 0;
	while (i < size)
	{
		graph->array[i].index = i;
		graph->array[i].name = ft_strdup(p->nodes->content);
		graph->array[i].source = (p->source == i) ? 1 : 0;
		graph->array[i].sink = (p->sink == i) ? 1 : 0;
		graph->array[i].x_coord = *(int *)p->x_coord->content;
		graph->array[i].y_coord = *(int *)p->y_coord->content;
		graph->array[i].bfs_marked = 0;
		graph->array[i].head = NULL;
		p->nodes = p->nodes->next;
		p->x_coord = p->x_coord->next;
		p->y_coord = p->y_coord->next;
		i++;
	}
	return (graph);
}
