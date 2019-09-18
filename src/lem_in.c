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

int8_t	get_ants(size_t *ants, char *line)
{
	if ((*ants = ft_atol(line)) < 1) 
		return (FAILURE);
	else
		return (SUCCESS);
}

int8_t	parse_line(char *line, size_t *ants)
{
	if (*ants == 0)
		return (get_ants(ants, line));
	return (SUCCESS);
}

int8_t	check_file(t_list *file)
{
	size_t	ants;
	size_t	size;
	
	ants = 0;
	size = 2;

	return (SUCCESS);
}

t_graph	*init_graph(t_graph *graph)
{
	char	*line;
	t_list	*new_line;
	t_list	*file;

	line = NULL;
	new_line = NULL;
	file = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if ((new_line = ft_lstnew(line, ft_strlen(line) * sizeof(char) + 1)) == NULL)
			return (exit_read_error(&file));
		if (file == NULL)
			file = new_line;
		else
			ft_lstappend(&file, new_line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (parse_file(file, graph) == FAILURE)
		return (NULL);		
	if ((graph = create_graph(graph->size)) == NULL)
		return (exit_graph_error());
	add_edge(graph, 0, 1);
	print_graph(graph);
	return (graph);
}

int		main(void)
{
	t_graph	*graph;

	graph = NULL;
	if ((graph = init_graph(graph)) == NULL)
		return (EXIT_FAILURE);
	if (exit_free_graph(graph) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
