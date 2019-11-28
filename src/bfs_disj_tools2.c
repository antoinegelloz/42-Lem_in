/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_disj_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:49:03 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 17:50:43 by ekelkel          ###   ########.fr       */
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
