/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/28 09:41:57 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define INCREASE 1
#define DECREASE -1

int8_t	change_capacity(t_graph *graph, t_list *u, t_list *v, int8_t order)
{
	t_edge *curr;

	//printf("u:%d\n", *(int *)u->content);
	//printf("v:%d\n", *(int *)v->content);
	curr = graph->array[*(int *)u->content].head;
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
	t_list	*curr;
	t_bfs	*new_bfs;

	aug_paths = NULL;
	new_bfs = NULL;
	//while (TRUE)
	//{
		if ((new_bfs = bfs(graph)) == NULL)
			return (aug_paths);
		ft_putendl("New aug_path:");
		print_ssize_t(new_bfs->best_path);
		ft_lstappend(&aug_paths, new_bfs->best_path);
		curr = new_bfs->best_path;
		while (curr->next)
		{
			change_capacity(graph, curr, curr->next, INCREASE);
			change_capacity(graph, curr->next, curr, DECREASE);
			curr = curr->next;
		}
	//}
	return (aug_paths);
}
