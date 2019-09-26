/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:00:34 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/26 12:04:37 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	exit_parsing_error(t_parsing *p, char **tab)
{
	ft_lstdel(&p->nodes, ft_delcontent);
	ft_lstdel(&p->x_coord, ft_delcontent);
	ft_lstdel(&p->y_coord, ft_delcontent);
	ft_lstdel(&p->file, ft_delcontent);
	free_tab(tab);
	ft_putendl_fd("PARSING ERROR", 2);
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

void	free_tab(char **tab)
{
	size_t i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
	}
	free(tab);
	tab = NULL;
}

int8_t	free_p(t_parsing *p)
{
	ft_lstdel(&p->nodes, ft_delcontent);
	ft_lstdel(&p->x_coord, ft_delcontent);
	ft_lstdel(&p->y_coord, ft_delcontent);
	ft_lstdel(&p->file, ft_delcontent);
	return (SUCCESS);
}

void	free_graph(t_graph *graph)
{
	size_t	i;

	if (graph == NULL)
		return ;
	i = 0;
	while (i < graph->size)
	{
		if (graph->array[i].name)
			ft_strdel(&graph->array[i].name);
		edge_del(&graph->array[i].head);
		i++;
	}
	free(graph->array);
	free(graph);
	graph = NULL;
}
