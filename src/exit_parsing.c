/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:20:51 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/19 14:18:59 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_p(t_parsing *p)
{
	ft_lstdel(&p->nodes, ft_delcontent);
	ft_lstdel(&p->x_coord, ft_delcontent);
	ft_lstdel(&p->y_coord, ft_delcontent);
	ft_lstdel(&p->from, ft_delcontent);
	ft_lstdel(&p->to, ft_delcontent);
	ft_lstdel(&p->file, ft_delcontent);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int8_t	exit_parsing_error(t_parsing *p, char *line, char **tab)
{
	if (p->ants > 0 && p->source > -1 && p->sink > -1
		&& p->nodes != NULL && p->from != NULL && p->to != NULL)
	{
		free_tab(tab);
		return (STOP);
	}
	if (line)
		ft_strdel(&line);
	free_p(p);
	free_tab(tab);
	ft_putendl_fd("ERROR", 2);
	return (FAILURE);
}
