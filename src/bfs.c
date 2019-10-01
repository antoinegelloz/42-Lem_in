/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/01 16:02:51 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_results(t_bfs *bfs, size_t size)
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

void			reset_marks_fail(t_graph *graph, t_bfs *bfs)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	while (i < (ssize_t)graph->size)
	{
		j = 0;
		while (bfs->queue[j] != -1)
		{
			if (i == bfs->queue[j])
				graph->nodes[i].bfs_marked = FALSE;
			j++;
		}
		i++;
	}
}

void			reset_marks(t_graph *graph, t_bfs *bfs)
{
	size_t	i;
	int8_t	found;
	t_list	*curr;

	i = 0;
	curr = NULL;
	found = FALSE;
	while (i < graph->size)
	{
		curr = bfs->shortest_path;
		while (curr != NULL)
		{
			printf("res:%zd\n", *(size_t *)curr->content);
			if (i == *(size_t *)curr->content)
			{
				ft_putendl("je rentre");
				found = TRUE;
				break ;
			}
			curr = curr->next;
		}
		if (found == FALSE || graph->nodes[i].sink == TRUE || graph->nodes[i].source == TRUE)
			graph->nodes[i].bfs_marked = FALSE;
		found = FALSE;
		i++;
	}
}

t_bfs	*reconstruct_path(t_bfs *bfs, t_graph *graph)
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
	if (graph->nodes[*(ssize_t *)bfs->shortest_path->content].source != TRUE)
	{
		reset_marks_fail(graph, bfs);
		ft_lstdel(&bfs->shortest_path, ft_delcontent);
		free_bfs(bfs);
		return (NULL);
	}
	reset_marks(graph, bfs);
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
			printf("node:%zd, neig:%zd, cap:%zu, mark:%zd\n", node, neighbours->dest, neighbours->capacity, graph->nodes[neighbours->dest].bfs_marked);
			print_graph(graph);
			if (graph->nodes[neighbours->dest].bfs_marked != TRUE && neighbours->capacity > 0)
			{
				enqueue(bfs, neighbours->dest);
				bfs->prev[neighbours->dest] = node;
				graph->nodes[neighbours->dest].bfs_marked = TRUE;
				//printf("mark:%zd\n", graph->nodes[1].bfs_marked);
			}
			print_results(bfs, graph->size);
			neighbours = neighbours->next;
		}
	}
	print_results(bfs, graph->size);
	return (reconstruct_path(bfs, graph));
}
