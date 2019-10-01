/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:00:34 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/30 17:14:03 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	exit_parsing_error(t_parsing *p, char *line, char **tab)
{
	if (line)
		ft_strdel(&line);
	ft_lstdel(&p->nodes, ft_delcontent);
	ft_lstdel(&p->x_coord, ft_delcontent);
	ft_lstdel(&p->y_coord, ft_delcontent);
	ft_lstdel(&p->from, ft_delcontent);
	ft_lstdel(&p->to, ft_delcontent);
	ft_lstdel(&p->file, ft_delcontent);
	free_tab(tab);
	ft_putendl_fd("PARSING ERROR", 2);
	return (FAILURE);
}

void	free_tab(char **tab)
{
	size_t i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_p(t_parsing *p)
{
	ft_lstdel(&p->nodes, ft_delcontent);
	ft_lstdel(&p->x_coord, ft_delcontent);
	ft_lstdel(&p->y_coord, ft_delcontent);
	ft_lstdel(&p->from, ft_delcontent);
	ft_lstdel(&p->to, ft_delcontent);
	ft_lstdel(&p->file, ft_delcontent);
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

void	free_graph(t_graph *graph)
{
	size_t	i;

	if (graph == NULL)
		return ;
	i = 0;
	while (i < graph->size)
	{
		ft_strdel(&graph->nodes[i].name);
		edge_del(&graph->nodes[i].head);
		i++;
	}
	free(graph->nodes);
	free(graph);
	graph = NULL;
}

void	free_bfs(t_bfs *bfs)
{
	free(bfs->prev);
	free(bfs->queue);
	free(bfs);
}
