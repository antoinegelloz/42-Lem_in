/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/27 14:59:35 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	reduce_capacity(t_list u, t_list v)
{

	return (SUCCESS);
}

t_list	edmonds_karp(t_graph *graph)
{
	t_list	paths;
	t_list	new_path;
	size_t	flow;

	flow = 0;
	paths = NULL;
	new_paths = NULL;
	while (TRUE)
	{
		if ((new_path = bfs(graph)) == NULL)
			return (paths);
		ft_lstappend(&paths, new_path);
		flow++;
		while (new_path)
		{
			reduce_capacity(new_path, new_path->next);
			increase_capacity(new_path->next, new_path);
			new_path = new_path->next;
		}
	}
	return (paths);
}
