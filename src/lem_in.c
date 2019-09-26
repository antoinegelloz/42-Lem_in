/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/26 12:21:54 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	save_node(char *line, t_parsing *p)
{
	char	**tab;
	t_list	*new_name;
	t_list	*new_x_coord;
	t_list	*new_y_coord;

	if ((tab = ft_strsplit(line, ' ')) == NULL)
		return (exit_parsing_error(p, tab));
	if ((new_name = ft_lstnew(tab[0], (ft_strlen(tab[0]) + 1)
					* sizeof(char))) == NULL)
			return (exit_parsing_error(p, tab));
	ft_lstappend(&p->nodes, new_name);
	if ((new_x_coord = ft_lstnew(tab[1], (ft_strlen(tab[1]) + 1)
					* sizeof(char))) == NULL)
			return (exit_parsing_error(p, tab));
	ft_lstappend(&p->x_coord, new_x_coord);
	if ((new_y_coord = ft_lstnew(tab[2], (ft_strlen(tab[2]) + 1)
					* sizeof(char))) == NULL)
			return (exit_parsing_error(p, tab));
	ft_lstappend(&p->y_coord, new_y_coord);
	free_tab(tab);
	return (SUCCESS);
}

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
				|| (ft_strequ("##start", line) && p->source != 0)
				|| (ft_strequ("##end", line) && p->sink != 0))
			return (FAILURE);
		p->is_prev_command = TRUE;
		if (ft_strequ("##start", line))
			p->source = p->node_index;
		if (ft_strequ("##end", line))
			p->sink = p->node_index;
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
		p->node_index++;

		return (save_node(line, p));
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

void	init_parsing(t_parsing *p)
{
	p->node_index = 0;
	p->ants = 0;
	p->is_prev_command = FALSE;
	p->source = 0;
	p->sink = 0;
	p->nodes = NULL;
	p->x_coord = NULL;
	p->y_coord = NULL;
	p->file = NULL;
}

int8_t	parse_file(t_parsing *p)
{
	int			ret;
	char		*line;
	t_list		*new_line;

	line = NULL;
	new_line = NULL;
	while ((ret = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		if (process_line(line, p) == FAILURE)
			return (exit_parsing_error(p, NULL));
		if ((new_line = ft_lstnew(line, (ft_strlen(line) + 1)
						* sizeof(char))) == NULL)
			return (exit_parsing_error(p, NULL));
		ft_lstappend(&p->file, new_line);
		ft_strdel(&line);
	}
	if (ret == FAILURE)
		ft_putendl_fd("READ ERROR", 2);
	ft_strdel(&line);
	get_next_line(CLEANUP, NULL);
	return (SUCCESS);
}

void	print_nodes(t_parsing *p)
{
	t_list		*curr;

	ft_putendl("Nodes:");
	curr = p->nodes;
	while (curr)
	{
		ft_putendl(curr->content);
		curr = curr->next;
	}
}

void	print_file(t_parsing *p)
{
	t_list		*curr;

	ft_putendl("File:");
	curr = p->file;
	while (curr)
	{
		ft_putendl(curr->content);
		curr = curr->next;
	}
}

int		main(void)
{
	t_parsing	p;
	t_graph		*graph;

	init_parsing(&p);
	graph = NULL;
	if (parse_file(&p) == FAILURE)
		return (EXIT_FAILURE);
	//if (build_graph(graph) == FAILURE)
	//	return (EXIT_FAILURE);
	ft_putendl("File saved successfully");
	print_nodes(&p);
	print_file(&p);
	graph = create_graph(ft_lstgetsize(p.nodes));
	print_graph(graph);
	free_p(&p);
	if (edmonds_karp(graph) == FAILURE)
		return (EXIT_FAILURE);
	free_graph(graph);
	return (EXIT_SUCCESS);
}
