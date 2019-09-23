/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/23 10:39:41 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	get_graph_size(t_list *file)
{
	size_t size;

	size = 0;
	while (file && file->next && (is_room(file->content)
				|| is_command(file->content)
				|| is_comment_or_false_command(file->content)))
	{
		if (is_command(file->content) && !is_room(file->next->content))
				return (FAILURE);
		else if (is_room(file->content))
			size++;	
		file = file->next;
	}
	if (size < 2 || !file || !is_tunnel(file->content))
		return (FAILURE);
	return (size);
}

int8_t	check_rooms(t_list *file, size_t size)
{
	(void)file;
	(void)size;
	return (SUCCESS);		
}

t_graph	*build_graph(t_list *file)
{
	t_graph	*graph;
	size_t	ants;
	size_t	size;

	ants = 0;
	graph = NULL;
	if (!is_ants(file->content) || (ants = ft_atol(file->content)) < 1)
		return (exit_graph_error(&file));
	if ((size = get_graph_size(file->next)) == FAILURE)
		return (exit_graph_error(&file));
	if (check_rooms(file->next, size) == FAILURE)
		return (exit_graph_error(&file));
	if ((graph = create_graph(size)) == NULL)
		return (exit_graph_error(&file));
	add_edge(graph, 0, 1);
	return (graph);
}

t_graph	*parse_file(void)
{
	t_graph	*graph;
	t_list	*file;
	t_list	*curr;

	if ((file = save_file()) == NULL)
		return (NULL);
	ft_printf("File saved successfully\n");
	curr = file;
	while (curr)
	{
		ft_printf("%s\n", curr->content);
		curr = curr->next;
	}
	graph = NULL;
	if ((graph = build_graph(file)) == NULL)
		return (NULL);
	ft_printf("Graph built successfully\n");
	ft_lstdel(&file, ft_delcontent);
	return (graph);
}

int		main(void)
{
	t_graph	*graph;

	graph = NULL;
	if ((graph = parse_file()) == NULL)
		return (EXIT_FAILURE);
	print_graph(graph);
	if (exit_free_graph(graph) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
