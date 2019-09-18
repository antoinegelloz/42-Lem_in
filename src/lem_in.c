/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/18 13:30:50 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int8_t	check_line(char *line)
{
	(void)line;
	return (SUCCESS);
}

t_graph	*parse_file(t_graph *graph)
{
	size_t	size;
	char	*line;

	size = 3;
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (check_line(line) == FAILURE)
			return (exit_parse_error());
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if ((graph = create_graph(size)) == NULL)
		return (exit_graph_error());
	add_edge(graph, 0, 1);
	print_graph(graph);
	return (graph);
}

int		main(void)
{
	t_graph	*graph;

	graph = NULL;
	if ((graph = parse_file(graph)) == NULL)
		return (EXIT_FAILURE);
	if (exit_free_graph(graph) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
