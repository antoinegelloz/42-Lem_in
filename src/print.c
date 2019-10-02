/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/10/02 09:31:48 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	print_graph(t_graph *graph)
{
	size_t	i;
	t_edge	*temp;

	if (graph == NULL)
		return ;
	ft_putendl("\n  Graph:");
	i = 0;
	while (i < graph->size)
	{
		temp = graph->nodes[i].head;
		if (graph->nodes[i].source == 1)
			ft_printf("s ");
		else if (graph->nodes[i].sink == 1)
			ft_printf("e ");
		else
			ft_printf("  ");
		ft_printf("Node|%d| Name|%s| x|%d| y|%d| mark|%d|", i, graph->nodes[i].name, graph->nodes[i].x_coord, graph->nodes[i].y_coord, graph->nodes[i].bfs_marked);
		while (temp)
		{
			ft_printf(" -> %d (%d)", temp->dest, temp->capacity);
			temp = temp->next;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("Source|%d| Sink|%d|\n", graph->source, graph->sink);
}

void	print_nodes_names(t_parsing *p)
{
	t_list		*curr;

	ft_putendl("\nNodes:");
	curr = p->nodes;
	while (curr)
	{
		ft_putendl(curr->content);
		curr = curr->next;
	}
}

void	print_coord_x(t_parsing *p)
{
	t_list		*curr;

	ft_putendl("\nx_coord:");
	curr = p->x_coord;
	while (curr)
	{
		ft_printf("x:%d\n", *(int *)curr->content);
		curr = curr->next;
	}
}

void	print_coord_y(t_parsing *p)
{
	t_list		*curr;

	ft_putendl("\ny_coord:");
	curr = p->y_coord;
	while (curr)
	{
		ft_printf("y:%d\n", *(int *)curr->content);
		curr = curr->next;
	}
}

void	print_edges(t_parsing *p)
{
	t_list		*curr_from;
	t_list		*curr_to;

	ft_putendl("\nEdges:");
	curr_from = p->from;
	curr_to = p->to;
	while (curr_from && curr_to)
	{
		printf("from:%zd to:%zd\n", *(size_t *)curr_from->content,
				*(size_t *)curr_to->content);
		curr_from = curr_from->next;
		curr_to = curr_to->next;
	}
}

void	print_file(t_parsing *p)
{
	t_list		*curr;

	ft_putendl("\nFile:");
	curr = p->file;
	while (curr)
	{
		ft_putendl(curr->content);
		curr = curr->next;
	}
	printf("\n");
}

void	print_ssize_t(t_list *list)
{
	t_list		*curr;

	ft_putstr("print ssize_t list: ");
	curr = list;
	while (curr)
	{
		printf("%zu ", *(ssize_t *)curr->content);
		curr = curr->next;
	}
	printf("\n");
}
