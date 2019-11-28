/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:32:38 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 18:15:15 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t		change_capacity(t_graph *graph, t_list *u, t_list *v, int8_t order)
{
	t_edge	*neighbours;

	neighbours = graph->nodes[*(size_t *)u->content].head;
	while (neighbours->dest != *(size_t *)v->content)
		neighbours = neighbours->next;
	if (neighbours->dest == *(size_t *)v->content)
	{
		if (order == INCREASE)
			neighbours->capacity++;
		if (order == DECREASE)
			neighbours->capacity--;
	}
	return (SUCCESS);
}

ssize_t		find_sink_index(t_graph *graph)
{
	ssize_t i;

	i = 0;
	while (i < (ssize_t)graph->size)
		i++;
	i = graph->size - 1;
	while (graph->nodes[i].sink == FALSE)
		i--;
	return (i);
}

t_bfs		*reconstruct_path(t_bfs *new_bfs, t_graph *graph)
{
	t_list	*tmp;
	ssize_t	i;
	size_t	j;

	tmp = NULL;
	i = find_sink_index(graph);
	j = 0;
	while (i != -1 && j <= graph->size)
	{
		if ((tmp = ft_lstnew(&i, sizeof(ssize_t))) == NULL)
			return (NULL);
		ft_lstadd(&new_bfs->shortest_path, tmp);
		i = new_bfs->prev[i];
		j++;
	}
	if (j > graph->size)
		ft_putendl("ERROR RECONSTRUCT PATH");
	if (graph->nodes[*(ssize_t *)new_bfs->shortest_path->content].source
		!= TRUE)
	{
		reset_marks_fail(graph, new_bfs);
		ft_lstdel(&new_bfs->shortest_path, ft_delcontent);
		free_bfs(new_bfs);
		return (NULL);
	}
	reset_marks(graph, new_bfs);
	tmp = new_bfs->shortest_path;
	while (tmp != NULL)
		tmp = tmp->next;
	return (new_bfs);
}

t_bfs		*bfs(t_graph *graph)
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
			}
			neighbours = neighbours->next;
		}
	}
	return (reconstruct_path(new_bfs, graph));
}
