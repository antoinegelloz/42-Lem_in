/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/28 11:09:10 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t	process_command(char *line, t_parsing *p)
{
	if (p->is_prev_command == TRUE
			|| (ft_strequ("##start", line) && p->source != -1)
			|| (ft_strequ("##end", line) && p->sink != -1))
		return (exit_parsing_error(p, line, NULL));
	p->is_prev_command = TRUE;
	if (ft_strequ("##start", line))
		p->source = p->index;
	if (ft_strequ("##end", line))
		p->sink = p->index;
	return (SUCCESS);
}

static int8_t	process_node(char *line, t_parsing *p)
{
	if (p->ants == 0 || p->from != NULL || p->to != NULL)
		return (exit_parsing_error(p, line, NULL));
	if (p->is_prev_command == TRUE)
		p->is_prev_command = FALSE;
	p->index++;
	return (save_node(p, line));
}

static int8_t	process_edge(char *line, t_parsing *p)
{
	if (p->is_prev_command == TRUE || p->nodes == NULL
			|| p->source == -1 || p->sink == -1 || p->ants == 0)
		return (exit_parsing_error(p, line, NULL));
	return (save_edge(p, line));
}

static int8_t	process_line(char *line, t_parsing *p)
{
	if (line == NULL)
		return (exit_parsing_error(p, line, NULL));
	if (is_ants(line) == SUCCESS)
	{
		if (p->ants != 0 || check_int(line, TRUE) == FAILURE)
			return (exit_parsing_error(p, line, NULL));
		p->ants = ft_atoi(line);
		return (SUCCESS);
	}
	if (is_command(line) == SUCCESS)
		return (process_command(line, p));
	if (is_comment_or_false_command(line) == SUCCESS
			&& p->is_prev_command == TRUE)
		return (exit_parsing_error(p, line, NULL));
	if (is_comment_or_false_command(line) == SUCCESS
			&& p->is_prev_command == FALSE)
		return (SUCCESS);
	if (is_node(line) == SUCCESS)
		return (process_node(line, p));
	if (is_edge(line) == SUCCESS)
		return (process_edge(line, p));
	return (exit_parsing_error(p, line, NULL));
}

int8_t			parse_file(t_parsing *p)
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
			return (exit_parsing_error(p, line, NULL));
		ft_lstappend(&p->file, new_line);
		ft_strdel(&line);
	}
	if (ret == FAILURE || p->from == NULL || p->to == NULL)
		exit_parsing_error(p, NULL, NULL);
	ft_strdel(&line);
	get_next_line(CLEANUP, NULL);
	return (SUCCESS);
}
