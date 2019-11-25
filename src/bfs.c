/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/25 17:57:29 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bfs			*reconstruct_path(t_bfs *new_bfs, t_graph *graph)
{
	t_list	*tmp;
	ssize_t	i;
	size_t	j;

	tmp = NULL;
	i = 0;
	//ft_putendl("RECONSTRUCT PATH");
	while (i < (ssize_t)graph->size)
	{
		//ft_printf("prev[%d]:%d\n", i, new_bfs->prev[i]);
		i++;
	}
	i = graph->size - 1;
	while (graph->nodes[i].sink == FALSE)
		i--;
	j = 0;
	while (i != -1 && j < graph->size)
	{
		tmp = ft_lstnew(&i, sizeof(ssize_t));
		ft_lstadd(&new_bfs->shortest_path, tmp);
		i = new_bfs->prev[i];
		j++;
	}
	if (j == graph->size)
		ft_putendl("ERROR RECONSTRUCT PATH");
	if (graph->nodes[*(ssize_t *)new_bfs->shortest_path->content].source != TRUE)
	{
		reset_marks_fail(graph, new_bfs);
		ft_lstdel(&new_bfs->shortest_path, ft_delcontent);
		free_bfs(new_bfs);
		ft_putendl("no path found");
		return (NULL);
	}
	reset_marks(graph, new_bfs);
	tmp = new_bfs->shortest_path;
	//ft_putendl("shortest path:");
	while (tmp != NULL)
	{
		ft_printf("%s ", graph->nodes[*(size_t *)tmp->content].name);
		tmp = tmp->next;
	}
	ft_putchar('\n');
	return (new_bfs);
}

t_bfs			*bfs(t_graph *graph)
{
	size_t	node;
	t_bfs	*new_bfs;
	t_edge	*neighbours;

	neighbours = NULL;
	new_bfs = init_bfs(graph);
	while (is_queue_empty(new_bfs) == FALSE)
	{
		node = dequeue(new_bfs);
		neighbours = graph->nodes[node].head;
		while (neighbours)
		{
			if (graph->nodes[neighbours->dest].bfs_marked != TRUE
					&& neighbours->capacity > 0)
			{
				enqueue(node, neighbours->dest, graph, new_bfs);
				ft_printf("EQ : %s\n", graph->nodes[neighbours->dest].name);
			}
			neighbours = neighbours->next;
		}
	}
	if ((new_bfs = reconstruct_path(new_bfs, graph)) != NULL)
	{
		graph->paths_count++;
		reset_marks(graph, new_bfs);
		return (new_bfs);
	}
	return (NULL);
}
