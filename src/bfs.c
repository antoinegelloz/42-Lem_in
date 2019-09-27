/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/27 16:29:24 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static size_t	find_pindex(ssize_t data, ssize_t *prev, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (prev[i] == data)
			break ;
		i++;
	}
	return (i);
}


void			reconstruct_path(t_queue *queue, t_graph *graph)
{
	t_list		*tmp;
	size_t		i;

	i = graph->size - 1;
	while (queue->out[i] == -1)
		i--;
	if (graph->array[queue->out[i]].sink == FALSE)
	   return ;	
	queue->best_path = ft_lstnew(&(queue->out[i]), sizeof(ssize_t));
	while (i > 0)
	{
		tmp = ft_lstnew(queue->prev + i, sizeof(ssize_t));
		ft_lstappend(&queue->best_path, tmp);	
		i = find_pindex(queue->prev[i], queue->out, graph->size);
	}
	ft_lstrev(&(queue->best_path));
	//printf("%zu", *(ssize_t*)queue->best_path->content);
	//queue->best_path = queue->best_path->next;
	//while (queue->best_path)
	//{
	//	printf(" -> %zu", *(ssize_t*)queue->best_path->content);
	//	queue->best_path = queue->best_path->next;
	//}
	//printf("\n");
	return ;
}

t_list			*bfs(t_graph *graph)
{
	size_t		i;
	size_t		j;
	t_queue 	*queue;
	t_edge		*lst;

	queue = create_queue(graph->size);
	j = 1;
	i = firstelt_queue(queue->out, queue, graph);
	while (isEmpty(queue) == FALSE)
	{
		i = find_index(queue->array[queue->front], graph->array, graph->size);
		graph->array[i].bfs_marked = TRUE;
		dequeue(queue);	
		lst = graph->array[i].head;
		while (lst)
		{
			if (graph->array[lst->dest].bfs_marked != TRUE)
			{
				enqueue(queue, lst->dest);
				queue->out[j] = lst->dest;
				queue->prev[j] = graph->array[i].index;
				j++;
			}
			lst = lst->next;
		}	
	}
	print_results(queue->out, queue->prev, graph->size);
	reconstruct_path(queue, graph);
	free_queue(queue);
	return (queue->best_path);
}
