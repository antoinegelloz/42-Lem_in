/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/25 18:14:06 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*edmonds_karp(t_graph *graph)
{
	t_list	*aug_paths;
	t_bfs	*new_bfs;
	t_list	*curr;

	aug_paths = NULL;
	new_bfs = NULL;
	curr = NULL;
	while (TRUE)
	{
		ft_putendl("BFS");
		if ((new_bfs = bfs(graph)) == NULL)
			return (aug_paths);
		ft_lstappend(&aug_paths, new_bfs->shortest_path);
		curr = new_bfs->shortest_path;
		while (curr->next != NULL)
		{
			change_capacity(graph, curr, curr->next, DECREASE);
			change_capacity(graph, curr->next, curr, INCREASE);
			curr = curr->next;
		}
		aug_paths = bfs_disjoint_paths(graph, aug_paths, new_bfs->shortest_path);
		free_bfs(new_bfs);
	}
	return (NULL);
}
