/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/30 16:44:40 by agelloz          ###   ########.fr       */
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

t_list	*find_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
	(void)graph;
	return (aug_paths);
}

t_list	*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_bfs	*new_bfs;
	t_list	*curr_path_node;

	aug_paths = NULL;
	new_bfs = NULL;
	curr_path_node = NULL;
	while (TRUE)
	{
		if ((new_bfs = bfs(graph)) == NULL)
			return (find_disjoint_paths(graph, aug_paths));
		ft_putendl("New shortest path found");
		ft_lstappend(&aug_paths, new_bfs->shortest_path);
		curr_path_node = new_bfs->shortest_path;
		while (curr_path_node->next != NULL)
		{
			change_capacity(graph, curr_path_node, curr_path_node->next, DECREASE);
			change_capacity(graph, curr_path_node->next, curr_path_node, INCREASE);
			curr_path_node = curr_path_node->next;
		}
	}
	return (aug_paths);
}
