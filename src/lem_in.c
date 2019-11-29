/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/29 15:56:22 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_options(t_options *o, int ac, char **av)
{
	int	i;

	o->help = FALSE;
	o->visual = FALSE;
	o->graph = FALSE;
	o->paths = FALSE;
	i = 1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-h") == TRUE
			|| ft_strequ(av[i], "--help") == TRUE)
			o->help = TRUE;
		if (ft_strequ(av[i], "-v") == TRUE
			|| ft_strequ(av[i], "--visual") == TRUE)
			o->visual = TRUE;
		if (ft_strequ(av[i], "-a") == TRUE
			|| ft_strequ(av[i], "--anthill") == TRUE)
			o->graph = TRUE;
		if (ft_strequ(av[i], "-p") == TRUE
			|| ft_strequ(av[i], "--paths") == TRUE)
			o->paths = TRUE;
		i++;
	}
}

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

int				main(int ac, char **av)
{
	t_options	o;
	t_parsing	p;
	t_graph		*graph;
	t_list		*aug_paths;

	init_options(&o, ac, av);
	init_parsing(&p);
	if (parse_file(&p) == FAILURE)
		return (EXIT_FAILURE);
	if ((graph = build_graph(&p)) == NULL)
		return (EXIT_FAILURE);
	if ((aug_paths = find_paths(graph)) == NULL)
		return (exit_bfs_error(&p, graph));
	print_file(&p);
	if (solver(graph, aug_paths, &o) == FAILURE)
		return (EXIT_FAILURE);
	ft_lstdel(&aug_paths, ft_delcontent);
	return (EXIT_SUCCESS);
}
