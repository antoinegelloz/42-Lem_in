/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/30 12:23:59 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define INCREASE 1
#define DECREASE -1

int8_t	change_capacity(t_graph *graph, t_list *u, t_list *v, int8_t order)
{
	t_edge *curr;

	curr = graph->nodes[*(int *)u->content].head;
	while (curr->dest != *(size_t *)v->content)
		curr = curr->next;
	if (curr->dest == *(size_t *)v->content)
	{
		if (order == INCREASE)
			curr->capacity++;
		if (order == DECREASE)
			curr->capacity--;
	}
	printf("new cap %zd->%zd: %zd\n", *(size_t *)u->content, *(size_t *)v->content, curr->capacity);
	return (SUCCESS);
}

int8_t	find_disjoint_paths(t_graph *graph, t_bfs *bfs)
{
	return (SUCCESS);
}

t_list	*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_bfs	*new_bfs;
	t_list	*curr_path;
	t_list	*curr_path_node;

	aug_paths = NULL;
	new_bfs = NULL;
	curr_path = NULL;
	curr_path_node = NULL;
	while (TRUE)
	{
		if ((new_bfs = bfs(graph)) == NULL)
			return (aug_paths);
		ft_putendl("New path found");
		find_disjoint_paths(graph, new_bfs);
		curr_path = new_bfs->paths;
		while (curr_path)
		{
			ft_lstappend(&aug_paths, curr_path);
			curr_path_node = curr->content;
			while (curr_path_node->next)
			{
				change_capacity(graph, curr_path_node, curr_path_node->next, DECREASE);
				change_capacity(graph, curr_path_node->next, curr_path_node, INCREASE);
			}
			curr_path = curr_path->next;
		}
	}
	return (aug_paths);
}
