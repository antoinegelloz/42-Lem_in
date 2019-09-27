/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/27 17:22:33 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define INCREASE 1
#define DECREASE -1

int8_t	change_capacity(t_graph *graph, t_list *u, t_list *v, int8_t order)
{
	t_edge *curr;

	curr = graph->array[*(size_t *)u->content].head;
	if (curr == NULL) 
		return (FAILURE);
	while (curr->dest != *(size_t *)v->content)
		curr = curr->next;
	if (curr == NULL || curr->dest != *(size_t *)v->content) 
		return (FAILURE);
	if (curr->dest == *(size_t *)v->content)
	{
		if (order == INCREASE)
			curr->capacity++;
		if (order == DECREASE)
			curr->capacity--;
	}
	return (SUCCESS);
}

t_list	*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_list	*new_path;

	aug_paths = NULL;
	new_path = NULL;
	while (TRUE)
	{
		if ((new_path = bfs(graph)) == NULL)
			return (aug_paths);
		ft_putendl("New aug_path:");
		print_list(new_path);
		ft_lstappend(&aug_paths, new_path);
		while (new_path)
		{
			change_capacity(graph, new_path, new_path->next, INCREASE);
			change_capacity(graph, new_path->next, new_path, DECREASE);
			new_path = new_path->next;
		}
	}
	return (aug_paths);
}
