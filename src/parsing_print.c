/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/27 17:19:22 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

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
}

void	print_list(t_list *list)
{
	t_list		*curr;

	curr = list;
	while (curr)
	{
		printf("%zd -> ", *(ssize_t *)curr->content);
		curr = curr->next;
	}
}
