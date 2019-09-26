/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/26 19:15:54 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		fill_tab(ssize_t *tab, size_t size)
{
	size_t		i;

	i = 0;

	while (i < size)
	{
		tab[i] = -1;
		i++;
	}
	return ;
}

static void		print_results(ssize_t *out, ssize_t *prev, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		printf("out[%zu] = %zd prev[%zu] = %zd\n", i, out[i], i, prev[i]);
		i++;
	}
	return ;
}

static size_t	find_index(int data, t_node *array, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (array[i].index == data)
			break ;
		i++;
	}
	return (i);
}

size_t			firstelt_queue(ssize_t *out, t_queue *queue, t_graph *graph)
{
	size_t			i;

	i = 0;
	while (i < graph->size)
	{
		if (graph->array[i].source == TRUE)
		{
			queue->array[0] = graph->array[i].index;
			enqueue(queue, graph->array[i].index);
			out[0]= queue->array[0];
			break;
		}
		i++;
	}
	return (i);
}

void			get_queue(t_graph *graph)
{
	size_t		i;
	size_t		j;
	t_queue 	*queue;
	t_edge		*lst;
	ssize_t		out[graph->size];
	ssize_t		prev[graph->size];

	queue = create_queue(graph->size);
	fill_tab(out, graph->size);
	fill_tab(prev, graph->size);
	j = 1;
	i = firstelt_queue(out, queue, graph);
	while (isEmpty(queue) == FALSE)
	{
		graph->array[i].bfs_marked = TRUE;
		dequeue(queue);	
		lst = graph->array[i].head;
		while (lst)
		{
			if (graph->array[lst->dest].bfs_marked != TRUE)
			{
				enqueue(queue, lst->dest);
				out[j] = lst->dest;
				prev[j] = graph->array[i].index;
				j++;
			}
			lst = lst->next;
		}
		if (isEmpty(queue) != 1)
			i = find_index(queue->array[queue->front], graph->array, graph->size);
	}
	print_results(out, prev, graph->size);
	return ;
}
