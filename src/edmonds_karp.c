/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/29 11:16:00 by agelloz          ###   ########.fr       */
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

t_list	*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_list	*curr;
	t_bfs	*new_bfs;

	curr = NULL;
	aug_paths = NULL;
	new_bfs = NULL;
	while (TRUE)
	{
		if ((new_bfs = bfs(graph)) == NULL)
			return (aug_paths);
		ft_putendl("New aug_path found");
		ft_lstappend(&aug_paths, new_bfs->best_path);
		curr = new_bfs->best_path;
		while (curr->next)
		{
			change_capacity(graph, curr, curr->next, DECREASE);
			change_capacity(graph, curr->next, curr, INCREASE);
			curr = curr->next;
		}
	}
	return (aug_paths);
}
