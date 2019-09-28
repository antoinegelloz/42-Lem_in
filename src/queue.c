/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:01:34 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/28 16:37:23 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	fill_tab(ssize_t *tab, size_t size)
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

t_bfs		*create_queue(size_t capacity) 
{ 
	t_bfs *bfs;

	bfs = (t_bfs *)malloc(sizeof(t_bfs)); 
	bfs->capacity = capacity; 
	bfs->front = 0;
	bfs->size = 0;  
	bfs->rear = capacity - 1;
	bfs->queue = (size_t *)malloc(bfs->capacity * sizeof(size_t));
	bfs->out = (ssize_t *)malloc(bfs->capacity * sizeof(ssize_t));
	bfs->prev = (ssize_t *)malloc(bfs->capacity * sizeof(ssize_t));
	fill_tab(bfs->out, bfs->capacity);
	fill_tab(bfs->prev, bfs->capacity);
	bfs->best_path = NULL;
	return (bfs); 
} 

int8_t		is_queue_full(t_bfs *bfs) 
{
	return (bfs->size == bfs->capacity);
} 

int8_t		is_queue_empty(t_bfs *bfs) 
{
	return (bfs->size == 0);
} 

void		enqueue(t_bfs *bfs, int data) 
{ 
	if (is_queue_full(bfs)) 
		return; 
	bfs->rear = (bfs->rear + 1) % bfs->capacity; 
	bfs->queue[bfs->rear] = data; 
	bfs->size = bfs->size + 1; 
	printf("%d enqueued to queue\n", data); 
} 

int			dequeue(t_bfs *bfs) 
{ 
	int		data;

	if (is_queue_empty(bfs))
		return (FAILURE);
	data = bfs->queue[bfs->front];
	bfs->front = (bfs->front + 1) % bfs->capacity;
	bfs->size = bfs->size - 1;
	printf("%d dequeued from queue\n", data);
	return (SUCCESS);
}
