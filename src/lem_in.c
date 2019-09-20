/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/20 13:00:58 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int8_t	is_tunnel(char *line)
{
	int	i;

	if (line == NULL)
		return (FAILURE);
	i = 0;
	while (line[i] != '\0' && line[i] != '-')
		if (!ft_isprint(line[i++]))
			return (FAILURE);
	if (line[i++] != '-')
		return (FAILURE);
	while (line[i] != '\0')
		if (!ft_isprint(line[i++]))
			return (FAILURE);
	return (SUCCESS);
}

int8_t	is_room(char *line)
{
	int	i;

	if (line == NULL)
		return (FAILURE);
	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
		if (!ft_isprint(line[i++]))
			return (FAILURE);
	if (line[i++] != ' ')
		return (FAILURE);
	while (line[i] != '\0' && line[i] != ' ')
		if (!ft_isdigit(line[i++]))
			return (FAILURE);
	if (line[i++] != ' ')
		return (FAILURE);
	while (line[i] != '\0')
		if (!ft_isdigit(line[i++]))
			return (FAILURE);
	return (SUCCESS);
}

int8_t	is_comment_or_false_command(char *line)
{
	if (line == NULL)
		return (FAILURE);
	if (line[0] == '#' && (line[1] != '#'
				|| !ft_strequ(line, "##start")
				|| !ft_strequ(line, "##end")))
		return (SUCCESS);
	else
		return (FAILURE);
}

int8_t	is_ants(char *line)
{
	int	i;

	if (line == NULL)
		return (FAILURE);
	i = 0;
	while (line[i] != '\0')
		if (!ft_isdigit(line[i++]))
			return (FAILURE);
	return (SUCCESS);
}

int8_t	is_command(char *line)
{
	if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		return (SUCCESS);
	else
		return (FAILURE);
}

int8_t	check_line(char **line)
{
	if (*line == NULL)
		return (FAILURE);
	if (is_command(*line))
		return (SUCCESS);
	if (is_comment_or_false_command(*line))
		return (SUCCESS);
	if (is_ants(*line))
		return (SUCCESS);
	if (is_room(*line))
		return (SUCCESS);
	if (is_tunnel(*line))
		return (SUCCESS);
	ft_strdel(line);
	return (FAILURE);
}

t_list	*save_file(void)
{
	char	*line;
	t_list	*new_line;
	t_list	*file;
	int		ret;

	file = NULL;
	line = NULL;
	new_line = NULL;
	while ((ret = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		if (check_line(&line) == FAILURE)
			return (NULL);
		if ((new_line = ft_lstnew(line, ft_strlen(line)
						* sizeof(char) + 1)) == NULL)
			return (NULL);
		if (file == NULL)
			file = new_line;
		else
			ft_lstappend(&file, new_line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (file);
}

t_graph	*build_graph(t_list *file)
{
	t_graph	*graph;
	size_t	ants;
	size_t	size;

	ants = 0;
	graph = NULL;
	if (!is_ants(file->content) || (ants = ft_atol(file->content)) < 1)
		return (NULL);
	file = file->next;
	size = 0;
	while (file && file->next && (is_room(file->content) || is_command(file->content)
									|| is_comment_or_false_command(file->content)))
	{
		if (is_command(file->content) && !is_room(file->next->content))
				return (NULL);
		else if (is_room(file->content))
			size++;	
	}
	if (!file || !is_tunnel(file->content))
		return (NULL);
	if ((graph = create_graph(size)) == NULL)
		return (NULL);
	if (size > 1)
		add_edge(graph, 0, 1);
	return (graph);
}


t_graph	*parse_file(void)
{
	t_graph	*graph;
	t_list	*file;

	if ((file = save_file()) == NULL)
	{
		exit_file_error(&file);
		return (NULL);
	}
	ft_printf("File saved in a linked list\n");
	graph = NULL;
	if ((graph = build_graph(file)) == NULL)
		return (exit_graph_error(&file));
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
