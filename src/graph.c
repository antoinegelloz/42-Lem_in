/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/18 12:13:55 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	print_graph(t_graph *graph)
{
	size_t	index;
	t_edge	*temp;

	index = 0;
	while (index < graph->size)
	{
		temp = graph->array[index].head;
		ft_printf("Adjacency list of node %d: head", index);
		while (temp)
		{
			ft_printf(" -> %d", temp->dest);
			temp = temp->next;
		}
		ft_printf("\n");
		index++;
	}
}

int8_t	add_edge(t_graph *graph, int src, int dest)
{
	t_edge *forward_edge; 
	t_edge *backward_edge; 

	if ((forward_edge = (t_edge *)malloc(sizeof(t_edge))) == FAILURE)
		return (FAILURE);
	forward_edge->dest = dest;
	forward_edge->next = graph->array[src].head;
	graph->array[src].head = forward_edge;
	if ((backward_edge = (t_edge *)malloc(sizeof(t_edge))) == FAILURE)
	{
		free(forward_edge);
		return (FAILURE);
	}
	backward_edge->dest = src;
	backward_edge->next = graph->array[dest].head;
	graph->array[dest].head = backward_edge;
	return (SUCCESS);
}

t_graph	*create_graph(size_t size)
{
	t_graph *graph;
	size_t	i;

	if (size == 0 || (graph = (t_graph *)malloc(sizeof(t_graph))) == FAILURE)
			return (NULL);
	graph->size = size;
	if ((graph->array = (t_node *)malloc(size * sizeof(t_node))) == FAILURE)
	{
		free(graph);
		return (NULL);
	}
	i = 0;
	while (i < size)
		graph->array[i++].head = NULL;
	return (graph);
}
