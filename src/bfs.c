/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/22 11:57:05 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bfs			*reconstruct_path(t_bfs *bfs, t_graph *graph)
{
	t_list	*tmp;
	ssize_t	i;

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
	if (graph->nodes[*(ssize_t *)bfs->shortest_path->content].source != TRUE)
	{
		reset_marks_fail(graph, bfs, TRUE);
		ft_lstdel(&bfs->shortest_path, ft_delcontent);
		free_bfs(bfs);
		return (NULL);
	}
	graph->paths_count++;
	reset_marks(graph, bfs, TRUE);
	ft_printf("first:%s\n", graph->nodes[*(size_t *)bfs->shortest_path->next->content].name);
	ft_putendl("NBFS:");
	print_ssize_t(bfs->shortest_path);
	return (bfs);
}

t_bfs			*bfs(t_graph *graph)
{
	size_t	node;
	t_bfs	*bfs;
	t_edge	*neighbours;

	neighbours = NULL;
	bfs = init_bfs(graph, TRUE);
	while (is_queue_empty(bfs) == FALSE)
	{
		node = dequeue(bfs);
		neighbours = graph->nodes[node].head;
		while (neighbours)
		{
			if (graph->nodes[neighbours->dest].bfs_marked != TRUE
					&& neighbours->capacity > 0)
			{
				enqueue(bfs, neighbours->dest);
				bfs->prev[neighbours->dest] = node;
				graph->nodes[neighbours->dest].bfs_marked = TRUE;
			}
			neighbours = neighbours->next;
		}
	}
	return (reconstruct_path(bfs, graph));
}
