/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/23 10:30:40 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
