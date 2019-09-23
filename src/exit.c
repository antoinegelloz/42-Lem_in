/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:00:34 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/23 10:15:51 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_graph	*exit_graph_error(t_list **file)
{
	ft_lstdel(file, ft_delcontent);
	ft_putendl_fd("GRAPH ERROR", 2);
	return (NULL);
}

t_list	*exit_file_error(t_list **file)
{
	ft_lstdel(file, ft_delcontent);
	ft_putendl_fd("FILE ERROR", 2);
	return (NULL);
}

int8_t	exit_free_graph(t_graph *graph)
{
	size_t	index;
	t_edge	*temp;
	t_edge	*node;

	index = 0;
	while (index < graph->size)
	{
		node = graph->array[index].head;
		while (node != NULL)
		{
			temp = node;
			node = node->next;
			free(temp);
			temp = NULL;
		}
		index++;
	}
	free(graph->array);
	free(graph);
	graph = NULL;
	return (SUCCESS);
}
