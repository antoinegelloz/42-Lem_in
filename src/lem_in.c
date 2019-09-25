/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/25 18:08:18 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	process_line(char *line, t_parsing *p)
{
	if (line == NULL)
		return (FAILURE);
	if (is_ants(line) == SUCCESS)
	{
		if (p->ants != 0 || (p->ants = ft_atol(line)) < 1)
			return (FAILURE);
		return (SUCCESS);
	}
	if (is_command(line) == SUCCESS)
	{
		if (p->is_prev_command == TRUE 
			|| (ft_strequ("##start", line) && p->is_start != 0)
			|| (ft_strequ("##end", line) && p->is_end != 0))
			return (FAILURE);
		p->is_prev_command = TRUE;
		if (ft_strequ("##start", line))
			p->is_start = p->room_index;
		if (ft_strequ("##end", line))
			p->is_end = p->room_index;
		return (SUCCESS);
	}
	if (is_comment_or_false_command(line) == SUCCESS)
	{
		if (p->is_prev_command == TRUE)
			return (FAILURE);
		return (SUCCESS);
	}
	if (is_node(line) == SUCCESS)
	{
		if (p->is_prev_command == TRUE)
			p->is_prev_command = FALSE;
		//save_node(line);
		p->room_index++;
		ft_putendl("node");
		return (SUCCESS);
	}
	if (is_edge(line) == SUCCESS)
	{
		if (p->is_prev_command == TRUE)
			return (FAILURE);
		return (SUCCESS);
	}
	ft_strdel(&line);
	return (FAILURE);
}

void	init(t_parsing *p)
{
	p->room_index = 0;
	p->ants = 0;
	p->size = 0;
	p->is_prev_command = FALSE;
	p->is_start = 0;
	p->is_end = 0;
	p->rooms = NULL;
	p->x_coord = NULL;
	p->y_coord = NULL;
	p->file = NULL;
}

int8_t	parse_file(t_parsing *p)
{
	int			ret;
	char		*line;

	line = NULL;
	while ((ret = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		if (process_line(line, p) == FAILURE)
			return (exit_parsing_error(p));
		ft_strdel(&line);
	}
	if (ret == FAILURE)
		ft_putendl_fd("READ ERROR", 2);
	ft_strdel(&line);
	get_next_line(CLEANUP, NULL);
	return (SUCCESS);
}

int		main(void)
{
	t_parsing	p;
	t_graph		*graph;

	init(&p);
	graph = NULL;
	//if (parse_file(&p) == FAILURE)
		//return (EXIT_FAILURE);
	//if (build_graph(graph) == FAILURE)
	//	return (EXIT_FAILURE);
	graph = create_graph(5);
	create_edge(graph, 0, 1);
	create_edge(graph, 1, 3);
	create_edge(graph, 3, 4);
	print_graph(graph);
	if (edmonds_karp(graph) == FAILURE)
		return (EXIT_FAILURE);
	free_graph(graph);
	return (EXIT_SUCCESS);
}
