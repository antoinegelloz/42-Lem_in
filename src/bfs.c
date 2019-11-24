/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/24 18:09:21 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bfs			*reconstruct_path(t_bfs *bfs, t_graph *graph)
{
	t_list	*tmp;
	ssize_t	i;
	size_t	j;

	tmp = NULL;
	i = 0;
	//ft_putendl("RECONSTRUCT PATH");
	while (i < (ssize_t)graph->size)
	{
		//ft_printf("prev[%d]:%d\n", i, bfs->prev[i]);
		i++;
	}
	i = graph->size - 1;
	while (graph->nodes[i].sink == FALSE)
		i--;
	j = 0;
	while (i != -1 && j < graph->size)
	{
		tmp = ft_lstnew(&i, sizeof(ssize_t));
		ft_lstadd(&bfs->shortest_path, tmp);
		i = bfs->prev[i];
		j++;
	}
	//if (j == graph->size)
	//	ft_putendl("ERROR RECONSTRUCT PATH");
	if (graph->nodes[*(ssize_t *)bfs->shortest_path->content].source != TRUE)
	{
		reset_marks_fail(graph, bfs, TRUE);
		ft_lstdel(&bfs->shortest_path, ft_delcontent);
		free_bfs(bfs);
		//ft_putendl("no path found");
		return (NULL);
	}
	graph->paths_count++;
	reset_marks(graph, bfs, TRUE);
	tmp = bfs->shortest_path;
	//ft_putendl("shortest path:");
	while (tmp != NULL)
	{
		//ft_printf("%s ", graph->nodes[*(size_t *)tmp->content].name);
		tmp = tmp->next;
	}
	//ft_putchar('\n');
	return (bfs);
}

t_bfs			*bfs(t_graph *graph)
{
	size_t	node;
	t_bfs	*bfs;
	t_edge	*neighbours;

	//ft_putendl("\nBFS");
	neighbours = NULL;
	bfs = init_bfs(graph);
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
