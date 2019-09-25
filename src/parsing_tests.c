/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/25 15:46:21 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	is_edge(char *line)
{
	int	i;

	if (line == NULL)
		return (FAILURE);
	i = 0;
	while (line[i] != '\0' && line[i] != '-')
		if (!ft_isalnum(line[i++]))
			return (FAILURE);
	if (line[i++] != '-')
		return (FAILURE);
	while (line[i] != '\0')
		if (!ft_isalnum(line[i++]))
			return (FAILURE);
	return (SUCCESS);
}

int8_t	is_node(char *line)
{
	int	i;

	if (line == NULL)
		return (FAILURE);
	i = 0;
	if (line[i] == 'L')
		return (FAILURE);
	while (line[i] != '\0' && line[i] != ' ')
		if (!ft_isalnum(line[i++]))
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
		if (line[0] == '0' || !ft_isdigit(line[i++]))
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
