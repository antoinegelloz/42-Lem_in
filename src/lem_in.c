/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/17 12:39:57 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	print_graph(t_graph *graph)
{
	int		index;
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

t_edge	*create_edge(int dest)
{
	t_edge *new_edge;

	new_edge = (t_edge *)malloc(sizeof(t_edge));
	new_edge->dest = dest;
	new_edge->next = NULL;
	return (new_edge);
}

void	add_edge(t_graph *graph, int src, int dest)
{
	t_edge *new_edge; 

	new_edge = create_edge(dest);
	new_edge->next = graph->array[src].head;
	graph->array[src].head = new_edge;
	new_edge = create_edge(src);
	new_edge->next = graph->array[dest].head;
	graph->array[dest].head = new_edge;
}

t_graph	*create_graph(int nodes)
{
	t_graph *graph;
	int		i;

	graph = (t_graph *)malloc(sizeof(t_graph));
	graph->size = nodes;
	graph->array = (t_node *)malloc(nodes * sizeof(t_node));
	i = 0;
	while (i < nodes)
	{
		graph->array[i].head = NULL;
		i++;
	}
	return (graph);
}

int		main(void)
{
	t_graph	*graph;
	int		nodes;

	nodes = 5;
	graph = create_graph(nodes);
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 1, 3);
	print_graph(graph);
	return (0);
}
