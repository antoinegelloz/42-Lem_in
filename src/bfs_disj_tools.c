/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_disj_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:44:12 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/28 19:28:04 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tmp_paths(t_paths *paths, t_graph *graph)
{
	size_t i;

	i = 0;
	while (i < graph->paths_count)
	{
		ft_lstdel(&paths->array[i], ft_delcontent);
		i++;
	}
	free(paths->array);
	free(paths->ants_to_paths);
	free(paths->n);
	free(paths->len);
	free(paths);
}

t_list	*build_path(t_edge *neighbours, t_graph *graph, t_list *new_aug_paths)
{
	t_list *tmp;

	tmp = NULL;
	while (neighbours->dest != graph->sink)
	{
		if (neighbours->capacity == 0)
		{
			if ((tmp = ft_lstnew(&neighbours->dest, sizeof(size_t))) == NULL)
				return (NULL);
			ft_lstappend(&new_aug_paths, tmp);
			neighbours = graph->nodes[neighbours->dest].head;
		}
		else
			neighbours = neighbours->next;
		if (neighbours->dest == graph->sink
				&& neighbours->capacity == 0)
		{
			if ((tmp = ft_lstnew(&neighbours->dest, sizeof(size_t))) == NULL)
				return (NULL);
			ft_lstappend(&new_aug_paths, tmp);
		}
	}
	return (new_aug_paths);
}

t_list	*rebuild_aug_paths(t_graph *graph)
{
	t_list		*new_aug_paths;
	t_list		*tmp;
	t_edge		*first_nodes;
	t_edge		*neighbours;

	new_aug_paths = NULL;
	tmp = NULL;
	first_nodes = graph->nodes[graph->source].head;
	while (first_nodes != NULL)
	{
		if (first_nodes->capacity == 0)
		{
			if ((tmp = ft_lstnew(&graph->source, sizeof(size_t))) == NULL)
				return (NULL);
			ft_lstappend(&new_aug_paths, tmp);
			if ((tmp = ft_lstnew(&first_nodes->dest, sizeof(size_t))) == NULL)
				return (NULL);
			ft_lstappend(&new_aug_paths, tmp);
			neighbours = graph->nodes[first_nodes->dest].head;
			new_aug_paths = build_path(neighbours, graph, new_aug_paths);
		}
		first_nodes = first_nodes->next;
	}
	return (new_aug_paths);
}

int8_t	is_new_solution_better(t_list *aug_paths, t_graph *graph)
{
	t_paths		*paths;
	size_t		new_output_lines;

	if ((paths = init_output(graph, aug_paths)) == NULL)
		return (FAILURE);
	find_solution(graph, paths);
	new_output_lines = paths->output_lines;
	free_tmp_paths(paths, graph);
	if (new_output_lines < graph->old_output_lines)
	{
		graph->old_output_lines = new_output_lines;
		return (TRUE);
	}
	return (FALSE);
}
