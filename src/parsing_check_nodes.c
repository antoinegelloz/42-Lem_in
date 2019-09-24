/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/24 17:54:12 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

int8_t	check_nodes_duplicates(t_graph *graph, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strequ(graph->array[i].name, graph->array[j].name))
				return (FAILURE);
			if (graph->array[i].x_coord == graph->array[j].x_coord
				&& graph->array[i].y_coord == graph->array[j].y_coord)
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

void	free_node_data(char **node_data)
{
	ft_strdel(&node_data[0]);
	ft_strdel(&node_data[1]);
	ft_strdel(&node_data[2]);
	free(node_data);
}

int8_t	check_nodes(t_graph *graph, t_list *file, size_t size)
{
	size_t		i;
	char		**node_data;

	i = 0;
	while (i < size)
	{
		is_comment_or_false_command(file->content) ? file = file->next : 0;
		ft_strequ(file->content, "##start") ? graph->array[i].source = 1 : 0;
		ft_strequ(file->content, "##end") ? graph->array[i].sink = 1 : 0;
		is_command(file->content) ? file = file->next : 0;
		if ((node_data = ft_strsplit(file->content, ' ')) == NULL)
			return (FAILURE);
		if ((graph->array[i].name = ft_strdup(node_data[0])) == NULL)
			return (exit_node_error(node_data));
		if (ft_atol(node_data[1]) < INT_MIN || ft_atol(node_data[1]) > INT_MAX
		|| ft_atol(node_data[2]) < INT_MIN || ft_atol(node_data[2]) > INT_MAX)
			return (exit_node_error(node_data));
		graph->array[i].x_coord = ft_atol(node_data[1]);
		graph->array[i].y_coord = ft_atol(node_data[2]);
		free_node_data(node_data);
		file = file->next;
		i++;
	}
	return (check_nodes_duplicates(graph, size));
}
