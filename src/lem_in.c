/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/22 10:42:20 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_parsing(t_parsing *p)
{
	p->index = 0;
	p->ants = 0;
	p->is_prev_command = FALSE;
	p->source = -1;
	p->sink = -1;
	p->nodes = NULL;
	p->x_coord = NULL;
	p->y_coord = NULL;
	p->from = NULL;
	p->to = NULL;
	p->file = NULL;
}

static t_graph	*build_graph(t_parsing *p)
{
	t_graph *graph;
	t_list	*curr_from;
	t_list	*curr_to;

	if ((graph = create_graph(p)) == NULL)
		return (NULL);
	curr_from = p->from;
	curr_to = p->to;
	while (curr_from != NULL && curr_to != NULL)
	{
		create_edge(graph, *(size_t *)curr_from->content,
				*(size_t *)curr_to->content);
		curr_from = curr_from->next;
		curr_to = curr_to->next;
	}
	return (graph);
}

int				main(int ac, char **av)
{
	t_parsing	p;
	t_graph		*graph;
	t_list		*aug_paths;

	init_parsing(&p);
	if (parse_file(&p) == FAILURE)
		return (EXIT_FAILURE);
	if ((graph = build_graph(&p)) == NULL)
		return (EXIT_FAILURE);
	if ((aug_paths = edmonds_karp(graph)) == NULL)
		return (exit_bfs_error(&p, graph));
	//print_graph(graph);
	//print_file(&p);
	free_p(&p);
	//ft_putendl("PATHS:");
	//print_ssize_t(aug_paths);
	if (ac == 2 && ft_strcmp(av[1], "-v") == 0)
		solver(graph, TRUE, aug_paths);
	else
		solver(graph, FALSE, aug_paths);
	free_graph(graph);
	ft_lstdel(&aug_paths, ft_delcontent);
	return (EXIT_SUCCESS);
}
