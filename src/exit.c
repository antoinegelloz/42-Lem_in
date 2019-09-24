/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:00:34 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/24 15:59:42 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	exit_node_error(char **node_data)
{
	if (node_data[0])
		free(node_data[0]);
	if (node_data[1])
		free(node_data[1]);
	if (node_data[2])
		free(node_data[2]);
	free(node_data);
	return (FAILURE);
}

void	edge_del(t_edge **edge)
{
	if (*edge)
	{
		edge_del(&(*edge)->next);
		if (edge)
		{
			free(*edge);
			*edge = NULL;
		}
	}
}

t_graph	*exit_graph_error(t_graph *graph, t_list *file)
{
	if (graph)
		free_graph(graph);
	ft_lstdel(&file, ft_delcontent);
	ft_putendl_fd("GRAPH ERROR", 2);
	return (NULL);
}

t_list	*exit_file_error(t_list **file)
{
	ft_lstdel(file, ft_delcontent);
	ft_putendl_fd("FILE ERROR", 2);
	return (NULL);
}

void	free_graph(t_graph *graph)
{
	size_t	index;

	index = 0;
	while (index < graph->size)
	{
		if (graph->array[index].name)
			ft_strdel(&graph->array[index].name);
		edge_del(&graph->array[index].head);
		index++;
	}
	free(graph->array);
	free(graph);
	graph = NULL;
}
