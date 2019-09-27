/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/27 13:29:45 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_parsing(t_parsing *p)
{
	p->index = 0;
	p->ants = 0;
	p->is_prev_command = FALSE;
	p->source = -1;
	p->sink = -1;
	p->nodes = NULL;
	p->x_coord = NULL;
	p->y_coord = NULL;
	p->file = NULL;
}

t_graph	*build_graph(t_parsing *p)
{
	t_graph *graph;
	t_list	*curr_from;
	t_list	*curr_to;

	if ((graph = create_graph(ft_lstgetsize(p->nodes))) == NULL)
		return (NULL);
	curr_from = p->from;
	curr_to = p->to;
	while (curr_from && curr_to)
	{
		create_edge(graph, *(size_t *)curr_from->content,
				*(size_t *)curr_to->content);
		curr_from = curr_from->next;
		curr_to = curr_to->next;
	}
	print_graph(graph);
	return (graph);
}

int		main(void)
{
	t_parsing	p;
	t_graph		*graph;

	init_parsing(&p);
	if (parse_file(&p) == FAILURE)
		return (EXIT_FAILURE);
//print_nodes_names(&p);
//print_coord_x(&p);
//print_coord_y(&p);
//print_edges(&p);
	if ((graph = build_graph(&p)) == NULL)
		return (EXIT_FAILURE);
  get_queue(graph);
	if (edmonds_karp(graph) == FAILURE)
		return (EXIT_FAILURE);
	print_file(&p);
	free_p(&p);
	free_graph(graph);
	return (EXIT_SUCCESS);
}
