/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/19 19:10:22 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*edmonds_karp(t_graph *graph)
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
		ft_lstappend(&aug_paths, new_bfs->shortest_path);
		curr_path_node = new_bfs->shortest_path;
		while (curr_path_node->next != NULL)
		{
			change_capacity(graph, curr_path_node,
					curr_path_node->next, DECREASE);
			change_capacity(graph, curr_path_node->next,
					curr_path_node, INCREASE);
			curr_path_node = curr_path_node->next;
		}
		free_bfs(new_bfs);
	}
	return (aug_paths);
}
