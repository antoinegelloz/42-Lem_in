/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/28 15:08:40 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_file(t_parsing *p)
{
	t_list		*curr;

	curr = p->file;
	while (curr)
	{
		ft_putendl(curr->content);
		curr = curr->next;
	}
	ft_putchar('\n');
	free_p(p);
}

void	print_ssize_t(t_list *list, t_graph *graph)
{
	t_list		*curr;

	curr = list;
	while (curr)
	{
		ft_printf("%s ", graph->nodes[*(size_t *)curr->content].name);
		curr = curr->next;
	}
	ft_putchar('\n');
}

void	print_graph(t_graph *graph)
{
	size_t	i;
	t_edge	*neighbours;

	ft_putendl("\n*** Anthill ***");
	i = 0;
	while (i < graph->size)
	{
		neighbours = graph->nodes[i].head;
		if (graph->nodes[i].source == 1)
			ft_putstr("start ");
		else if (graph->nodes[i].sink == 1)
			ft_putstr("  end ");
		else
			ft_putstr("      ");
		ft_printf("Room|%s| x|%d| y|%d| tunnels|", graph->nodes[i].name,
					graph->nodes[i].x_coord, graph->nodes[i].y_coord);
		while (neighbours)
		{
			ft_printf(" -> %s", graph->nodes[neighbours->dest].name);
			neighbours = neighbours->next;
		}
		ft_putstr("|\n");
		i++;
	}
}
