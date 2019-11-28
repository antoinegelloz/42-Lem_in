/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:49:03 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 22:42:34 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	is_on_path(size_t node, t_list *path, t_graph *graph)
{
	t_list	*curr;

	curr = path;
	while (curr != NULL && *(size_t *)curr->content != graph->sink)
	{
		if (*(size_t *)curr->content == node
				&& node != graph->source && node != graph->sink)
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

size_t	compute_path_pos(t_list **path, t_list *aug_paths, t_graph *graph)
{
	size_t	path_pos;
	t_list	*curr;

	path_pos = 0;
	curr = aug_paths;
	while (curr != *path)
	{
		if (*(size_t *)curr->content == graph->source)
			path_pos++;
		curr = curr->next;
	}
	return (path_pos);
}

t_list	*get_next_path(t_list *path, t_graph *graph)
{
	t_list	*next_path;

	next_path = path;
	while (next_path->next != NULL &&
			*(size_t *)next_path->next->content != graph->source)
		next_path = next_path->next;
	next_path = next_path->next;
	return (next_path);
}

void	change_capacity(t_graph *graph, t_list *u, t_list *v, int8_t order)
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
}

void	update_edge_capacities(t_bfs *new_bfs, t_graph *graph, int8_t order)
{
	t_list	*curr;

	curr = new_bfs->shortest_path;
	while (curr->next != NULL)
	{
		if (order == INCREASE)
		{
			change_capacity(graph, curr, curr->next, DECREASE);
			change_capacity(graph, curr->next, curr, INCREASE);
		}
		else
		{
			change_capacity(graph, curr, curr->next, INCREASE);
			change_capacity(graph, curr->next, curr, DECREASE);
		}
		curr = curr->next;
	}
	graph->paths_count += order;
}
