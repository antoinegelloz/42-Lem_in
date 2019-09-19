/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/19 19:28:24 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int8_t	is_correct_tunnel(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '-')
		if (!ft_isprint(i++))
			return (FAILURE);
	if (line[i++] != '-')
		return (FAILURE);
	while (line[i] != '\0')
		if (!ft_isprint(i++))
			return (FAILURE);
	return (SUCCESS);
}

int8_t	is_correct_room(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
		if (!ft_isprint(i++))
			return (FAILURE);
	if (line[i++] != ' ')
		return (FAILURE);
	while (line[i] != '\0' && line[i] != ' ')
		if (!ft_isdigit(i++))
			return (FAILURE);
	if (line[i++] != ' ')
		return (FAILURE);
	while (line[i] != '\0')
		if (!ft_isdigit(i++))
			return (FAILURE);
	return (SUCCESS);
}

int8_t	is_comment_or_false_command(char *line)
{
	if (line[0] == '#' && (line[1] != '#'
				|| !ft_strequ(line, "##start")
				|| !ft_strequ(line, "##end")))
		return (SUCCESS);
	else
		return (FAILURE);
}

int8_t	is_correct_ants(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
		if (!ft_isdigit(line[i++]))
			return (FAILURE);
	return (SUCCESS);
}

int8_t	check_line(char *line, t_list *file)
{
	(void)file;
	if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		return (SUCCESS);
	if (is_comment_or_false_command(line))
		return (SUCCESS);
	if (is_correct_ants(line))
		return (SUCCESS);
	if (is_correct_room(line))
		return (SUCCESS);
	if (is_correct_tunnel(line))
		return (SUCCESS);
	return (FAILURE);
}

t_list	*malloc_file(void)
{
	char	*line;
	t_list	*new_line;
	t_list	*file;

	file = NULL;
	line = NULL;
	new_line = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (check_line(line, file) == FAILURE)
			return (exit_read_error(&file));
		if ((new_line = ft_lstnew(line, ft_strlen(line)
						* sizeof(char) + 1)) == NULL)
			return (exit_read_error(&file));
		if (file == NULL)
			file = new_line;
		else
			ft_lstappend(&file, new_line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (file);
}

t_graph	*parse_file(void)
{
	t_graph	*graph;
	t_list	*file;

	file = malloc_file();
	ft_printf("File saved in a linked list\n");
	graph = NULL;
	if ((graph = create_graph(3)) == NULL)
		return (exit_graph_error());
	add_edge(graph, 0, 1);
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
