/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:44:12 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 23:35:42 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*add_node2paths(size_t *node, t_list **aug_paths)
{
	t_list	*tmp;

	if ((tmp = ft_lstnew(node, sizeof(size_t))) == NULL)
		return (NULL);
	ft_lstappend(aug_paths, tmp);
	return (tmp);
}

t_list	*rebuild_paths2(t_edge *neighbours, t_graph *graph, t_list *aug_paths)
{
	while (neighbours->dest != graph->sink)
	{
		if (neighbours->capacity == 0)
		{
			if (add_node2paths(&neighbours->dest, &aug_paths) == NULL)
				return (NULL);
			neighbours = graph->nodes[neighbours->dest].head;
		}
		else
			neighbours = neighbours->next;
		if (neighbours->dest == graph->sink
			&& neighbours->capacity == 0
			&& add_node2paths(&neighbours->dest, &aug_paths) == NULL)
			return (NULL);
	}
	return (aug_paths);
}

t_list	*rebuild_paths(t_graph *graph)
{
	t_list		*aug_paths;
	t_edge		*first_nodes;
	t_edge		*neighbours;

	aug_paths = NULL;
	first_nodes = graph->nodes[graph->source].head;
	while (first_nodes != NULL)
	{
		if (first_nodes->capacity == 0)
		{
			if (add_node2paths(&graph->source, &aug_paths) == NULL
				|| add_node2paths(&first_nodes->dest, &aug_paths) == NULL)
				return (NULL);
			neighbours = graph->nodes[first_nodes->dest].head;
			aug_paths = rebuild_paths2(neighbours, graph, aug_paths);
		}
		first_nodes = first_nodes->next;
	}
	return (aug_paths);
}

int8_t	is_new_solution_better(t_list *aug_paths, t_graph *graph)
{
	t_paths		*paths;
	size_t		new_output_lines;

	if ((paths = find_solution(graph, aug_paths)) == NULL)
		return (FAILURE);
	new_output_lines = paths->output_lines;
	free_paths(paths, graph);
	if (new_output_lines < graph->old_output_lines)
	{
		graph->old_output_lines = new_output_lines;
		return (TRUE);
	}
	return (FALSE);
}
