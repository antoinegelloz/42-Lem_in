/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:01:34 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/26 19:04:47 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*create_queue(unsigned capacity) 
{ 
	t_queue *queue;
	queue = (t_queue*) malloc(sizeof(t_queue)); 
	queue->capacity = capacity; 
	queue->front = 0;
	queue->size = 0;  
	queue->rear = capacity - 1;
	queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
	return queue; 
} 

int isFull(t_queue *queue) 
{
	return (queue->size == queue->capacity);
} 

int isEmpty(t_queue *queue) 
{
	return (queue->size == 0);
} 

void enqueue(t_queue *queue, int data) 
{ 
	if (isFull(queue)) 
		return; 
	queue->rear = (queue->rear + 1)%queue->capacity; 
	queue->array[queue->rear] = data; 
	queue->size = queue->size + 1; 
	printf("%d enqueued to queue\n", data); 
} 

int dequeue(t_queue *queue) 
{ 
	int		data;

	if (isEmpty(queue)) 
		return (FAILURE);
	data = queue->array[queue->front];	
	queue->front = (queue->front + 1)%queue->capacity; 
	queue->size = queue->size - 1;
	printf("%d dequeued from queue\n", data);
	return SUCCESS; 
}
