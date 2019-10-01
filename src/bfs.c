/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/30 17:28:24 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_results(t_bfs *bfs, size_t size)
{
	size_t	i;
	ssize_t *currq;
	ssize_t *currp;

	i = 0;
	currq = bfs->queue;
	currp = bfs->prev;
	while (i < size)
	{
		printf("queue[%2zu] = %2zd prev[%2zu] = %2zd\n", i, currq[i], i, currp[i]);
		i++;
	}
	ft_putchar('\n');
	return ;
}

void			reset_marks(t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->size)
	{
		graph->nodes[i].bfs_marked = 0;
		i++;
	}
}

static t_bfs	*reconstruct_path(t_bfs *bfs, t_graph *graph)
{
	t_list		*tmp;
	ssize_t		i;

	tmp = NULL;
	i = graph->size - 1;
	while (graph->nodes[i].sink == FALSE)
		i--;
	while (i != -1)
	{
		tmp = ft_lstnew(&i, sizeof(ssize_t));
		ft_lstadd(&bfs->shortest_path, tmp);
		i = bfs->prev[i];
	}
	print_ssize_t(bfs->shortest_path);
	reset_marks(graph);
	if (graph->nodes[*(ssize_t *)bfs->shortest_path->content].source != TRUE)
	{
		ft_lstdel(&bfs->shortest_path, ft_delcontent);
		free_bfs(bfs);
		return (NULL);
	}
	return (bfs);
}

t_bfs			*bfs(t_graph *graph)
{
	size_t		node;
	t_bfs 		*bfs;
	t_edge		*neighbours;

	neighbours = NULL;
	bfs = init_bfs(graph);
	while (is_queue_empty(bfs) == FALSE)
	{
		node = dequeue(bfs);
		neighbours = graph->nodes[node].head;
		while (neighbours)
		{
			if (graph->nodes[neighbours->dest].bfs_marked != TRUE && neighbours->capacity > 0)
			{
				enqueue(bfs, neighbours->dest);
				bfs->prev[neighbours->dest] = node;
				graph->nodes[neighbours->dest].bfs_marked = TRUE;
			}
			print_results(bfs, graph->size);
			neighbours = neighbours->next;
		}
	}
	print_results(bfs, graph->size);
	return (reconstruct_path(bfs, graph));
}
