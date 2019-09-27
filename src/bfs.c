/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/27 18:28:27 by agelloz          ###   ########.fr       */
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

size_t			firstelt_queue(ssize_t *out, t_bfs *bfs, t_graph *graph)
{
	size_t			i;

	i = 0;
	while (i < graph->size)
	{
		if (graph->array[i].source == TRUE)
		{
			bfs->array[0] = graph->array[i].index;
			enqueue(bfs, graph->array[i].index);
			out[0]= bfs->array[0];
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


void			reconstruct_path(t_bfs *bfs, t_graph *graph)
{
	t_list		*tmp;
	size_t		i;

	i = graph->size - 1;
	while (bfs->out[i] == -1)
		i--;
	if (graph->array[bfs->out[i]].sink == FALSE)
	   return ;	
	bfs->best_path = ft_lstnew(&(bfs->out[i]), sizeof(ssize_t));
	while (i > 0)
	{
		tmp = ft_lstnew(bfs->prev + i, sizeof(ssize_t));
		ft_lstappend(&bfs->best_path, tmp);	
		i = find_pindex(bfs->prev[i], bfs->out, graph->size);
	}
	ft_lstrev(&(bfs->best_path));
	//printf("%zu", *(ssize_t*)bfs->best_path->content);
	//bfs->best_path = bfs->best_path->next;
	//while (bfs->best_path)
	//{
	//	printf(" -> %zu", *(ssize_t*)bfs->best_path->content);
	//	bfs->best_path = bfs->best_path->next;
	//}
	//printf("\n");
	return ;
}

t_bfs	*bfs(t_graph *graph)
{
	size_t		i;
	size_t		j;
	t_bfs 	*bfs;
	t_edge		*lst;

	bfs = create_queue(graph->size);
	j = 1;
	i = firstelt_queue(bfs->out, bfs, graph);
	while (isEmpty(bfs) == FALSE)
	{
		i = find_index(bfs->array[bfs->front], graph->array, graph->size);
		graph->array[i].bfs_marked = TRUE;
		dequeue(bfs);	
		lst = graph->array[i].head;
		while (lst)
		{
			if (graph->array[lst->dest].bfs_marked != TRUE)
			{
				enqueue(bfs, lst->dest);
				bfs->out[j] = lst->dest;
				bfs->prev[j] = graph->array[i].index;
				j++;
			}
			lst = lst->next;
		}	
	}
	print_results(bfs->out, bfs->prev, graph->size);
	reconstruct_path(bfs, graph);
	return (bfs);
}
