/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:20:51 by ekelkel           #+#    #+#             */
/*   Updated: 2019/10/14 16:22:35 by ekelkel          ###   ########.fr       */
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

int8_t	exit_parsing_error(t_parsing *p, char *line, char **tab)
{
	if (line)
		ft_strdel(&line);
	free_p(p);
	free_tab(tab);
	ft_putendl_fd("ERROR", 2);
	return (FAILURE);
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
