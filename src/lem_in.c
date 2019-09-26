/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/26 18:54:18 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	init_parsing(t_parsing *p)
{
	p->node_index = 0;
	p->ants = 0;
	p->is_prev_command = FALSE;
	p->source = -1;
	p->sink = -1;
	p->nodes = NULL;
	p->x_coord = NULL;
	p->y_coord = NULL;
	p->file = NULL;
}

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
		printf("from:%zd to:%zd\n", *(size_t *)curr_from->content, *(size_t *)curr_to->content);
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

int8_t	is_coord_duplicate(t_parsing *p, int x, int y)
{
	t_list *xs;
	t_list *ys;

	xs = p->x_coord;
	ys = p->y_coord;
	while (xs && ys)
	{
		if (x == *(int *)xs->content && y == *(int *)ys->content)
			return (FAILURE);
		xs = xs->next;
		ys = ys->next;
	}
	return (SUCCESS);
}

ssize_t	get_node_index(char *name, t_list *nodes)
{
	t_list	*curr;
	ssize_t	index;

	index = 0;
	curr = nodes;
	while (curr)
	{
		if (ft_strequ((char *)curr->content, name))
			return (index);
		curr = curr->next;
		index++;
	}
	return (FAILURE);
}

int8_t	is_name_duplicate(t_parsing *p, char *new_name)
{
	t_list *names;

	names = p->nodes;
	while (names)
	{
		if (ft_strequ((char *)names->content, new_name))
			return (FAILURE);
		names = names->next;
	}
	return (SUCCESS);
}

int8_t	save_edge(char *line, t_parsing *p)
{
	char	**tab;
	t_list	*new_from;
	t_list	*new_to;
	ssize_t	from_index;
	ssize_t	to_index;

	if ((tab = ft_strsplit(line, '-')) == NULL)
		return (exit_parsing_error(p, tab));
	if ((from_index = get_node_index(tab[0], p->nodes)) == FAILURE)
			return (exit_parsing_error(p, tab));
	if ((to_index = get_node_index(tab[1], p->nodes)) == FAILURE)
			return (exit_parsing_error(p, tab));
	if ((new_from = ft_lstnew(&from_index, sizeof(ssize_t))) == NULL)
			return (exit_parsing_error(p, tab));
	if ((new_to = ft_lstnew(&to_index, sizeof(ssize_t))) == NULL || new_from == new_to)
			return (exit_parsing_error(p, tab));
	ft_lstappend(&p->from, new_from);
	ft_lstappend(&p->to, new_to);
	free_tab(tab);
	return (SUCCESS);
}

int8_t	save_node(char *line, t_parsing *p)
{
	char	**tab;
	t_list	*new_name;
	t_list	*new_x_coord;
	t_list	*new_y_coord;
	int		x;
	int		y;

	if ((tab = ft_strsplit(line, ' ')) == NULL)
		return (exit_parsing_error(p, tab));
	if ((new_name = ft_lstnew(tab[0], (ft_strlen(tab[0]) + 1)
					* sizeof(char))) == NULL)
			return (exit_parsing_error(p, tab));
	if (is_name_duplicate(p, new_name->content) == FAILURE)
		return (exit_parsing_error(p, tab));
	ft_lstappend(&p->nodes, new_name);
	if (ft_atol(tab[1]) < 1 || ft_atol(tab[1]) < INT_MIN || ft_atol(tab[1]) > INT_MAX)
			return (exit_parsing_error(p, tab));
	x = ft_atoi(tab[1]);
	if ((new_x_coord = ft_lstnew(&x, sizeof(int))) == NULL)
			return (exit_parsing_error(p, tab));
	if (ft_atol(tab[2]) < 1 || ft_atol(tab[2]) < INT_MIN || ft_atol(tab[1]) > INT_MAX)
			return (exit_parsing_error(p, tab));
	y = ft_atoi(tab[2]);
	if ((new_y_coord = ft_lstnew(&y, sizeof(int))) == NULL)
			return (exit_parsing_error(p, tab));
	if (is_coord_duplicate(p, x, y) == FAILURE)
		return (exit_parsing_error(p, tab));
	ft_lstappend(&p->x_coord, new_x_coord);
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
		if (p->ants != 0 || ft_atol(line) < 1)
			return (exit_parsing_error(p, NULL));
		p->ants = ft_atoi(line);
		return (SUCCESS);
	}
	if (is_command(line) == SUCCESS)
	{
		if (p->is_prev_command == TRUE 
				|| (ft_strequ("##start", line) && p->source != -1)
				|| (ft_strequ("##end", line) && p->sink != -1))
			return (exit_parsing_error(p, NULL));
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
			return (exit_parsing_error(p, NULL));
		return (SUCCESS);
	}
	if (is_node(line) == SUCCESS)
	{
		if (p->from != NULL || p->to != NULL)
			return (exit_parsing_error(p, NULL));
		if (p->is_prev_command == TRUE)
			p->is_prev_command = FALSE;
		p->node_index++;
		return (save_node(line, p));
	}
	if (is_edge(line) == SUCCESS)
	{
		if (p->is_prev_command == TRUE || p->nodes == NULL || p->source == -1 || p->sink == -1)
			return (exit_parsing_error(p, NULL));
		return (save_edge(line, p));
	}
	ft_strdel(&line);
	return (exit_parsing_error(p, NULL));
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
			return (FAILURE);
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
	if (p->file == NULL)
		return (exit_parsing_error(p, NULL));
	return (SUCCESS);
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
		create_edge(graph, *(size_t *)curr_from->content, *(size_t *)curr_to->content);
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
	ft_putendl("File saved successfully");
	//print_nodes_names(&p);
	//print_coord_x(&p);
	//print_coord_y(&p);
	//print_edges(&p);
	print_file(&p);
	if ((graph = build_graph(&p)) == NULL)
		return (EXIT_FAILURE);
	free_p(&p);
	if (edmonds_karp(graph) == FAILURE)
		return (EXIT_FAILURE);
	free_graph(graph);
	return (EXIT_SUCCESS);
}
