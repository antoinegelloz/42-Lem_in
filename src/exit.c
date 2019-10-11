/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:00:34 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/11 17:06:34 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_paths(t_paths *paths, t_graph *graph)
{
	size_t		i;

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
	free(paths->available);
	free(paths);
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

int	exit_bfs_error(t_parsing *p, t_graph *graph)
{
	free_p(p);
	free_graph(graph);	
	ft_putendl_fd("ERROR", 2);
	return (EXIT_SUCCESS);
}

int8_t	exit_parsing_error(t_parsing *p, char *line, char **tab)
{
	if (line)
		ft_strdel(&line);
	free_p(p);
	free_tab(tab);
	ft_putendl_fd("ERROR", 2);
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
