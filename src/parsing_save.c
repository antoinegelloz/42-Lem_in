/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/24 18:54:52 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	check_line2(char *line, t_list *file)
{
	return (SUCCESS);
}

int8_t	check_line(char *line, t_list *file)
{
	if (line == NULL)
		return (FAILURE);
	if (is_command(line))
		return (check_line2(line, file));
	if (is_comment_or_false_command(line))
		return (check_line2(line, file));
	if (is_ants(line))
		return (check_line2(line, file));
	if (is_node(line))
		return (check_line2(line, file));
	if (is_edge(line))
		return (check_line2(line, file));
	ft_strdel(&line);
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
		if (check_line(line, file) == FAILURE)
			return (exit_file_error(&file));
		if ((new_line = ft_lstnew(line, ft_strlen(line)
						* sizeof(char) + 1)) == NULL)
			return (exit_file_error(&file));
		ft_lstappend(&file, new_line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (file);
}
