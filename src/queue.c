/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:01:34 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/24 18:44:59 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

struct t_queue* create_queue(unsigned capacity) 
{ 
	struct t_queue* queue = (struct t_queue*) malloc(sizeof(struct t_queue)); 
	queue->capacity = capacity; 
	queue->front = 0;
	queue->size = 0;  
	queue->rear = capacity - 1;
	queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
	return queue; 
} 

int isFull(struct t_queue* queue) 
{
	return (queue->size == queue->capacity);
} 

int isEmpty(struct t_queue* queue) 
{
	return (queue->size == 0);
} 

void enqueue(struct t_queue* queue, int data) 
{ 
	if (isFull(queue)) 
		return; 
	queue->rear = (queue->rear + 1)%queue->capacity; 
	queue->array[queue->rear] = data; 
	queue->size = queue->size + 1; 
	printf("%d enqueued to queue\n", data); 
} 

int dequeue(struct t_queue* queue) 
{ 
	if (isEmpty(queue)) 
		return (FAILURE); 
	int data = queue->array[queue->front]; 
	queue->front = (queue->front + 1)%queue->capacity; 
	queue->size = queue->size - 1; 
	return SUCCESS; 
}

int main() 
{ 
	struct t_queue* queue = create_queue(1000); 

	enqueue(queue, 10); 
	enqueue(queue, 20); 
	enqueue(queue, 30); 
	enqueue(queue, 40); 
	return 0; 
} 
