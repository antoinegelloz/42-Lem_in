/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tests2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:35 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/29 17:03:38 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	check_int(char *nb, int8_t pos)
{
	int		i;
	int		neg;
	char	*tmp;

	i = 0;
	neg = FALSE;
	tmp = nb;
	if (*tmp == '-')
	{
		neg = TRUE;
		tmp++;
	}
	else if (*tmp == '+')
		tmp++;
	if (*tmp == '\0' || (pos == TRUE && (neg == TRUE || *tmp == '0')))
		return (FAILURE);
	while (*tmp)
		if (*tmp < '0' || *tmp++ > '9' || ++i > 10)
			return (FAILURE);
	if (i == 10 && ((neg && ft_strcmp(nb + 1, "2147483648") > 0)
				|| (!neg && ft_strcmp(nb, "2147483647") > 0)))
		return (FAILURE);
	return (SUCCESS);
}

int8_t	is_name_duplicate(t_parsing *p, char *new_name)
{
	t_list *names;

	names = p->nodes;
	while (names)
	{
		if (ft_strequ((char *)names->content, new_name))
			return (TRUE);
		names = names->next;
	}
	return (FALSE);
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
			return (TRUE);
		xs = xs->next;
		ys = ys->next;
	}
	return (FALSE);
}

int8_t	is_edge_duplicate(t_parsing *p, t_list *new_f, t_list *new_t)
{
	t_list *f;
	t_list *t;

	f = p->from;
	t = p->to;
	while (f && t)
	{
		if ((*(size_t *)new_f->content == *(size_t *)f->content
			&& *(size_t *)new_t->content == *(size_t *)t->content)
			|| (*(size_t *)new_f->content == *(size_t *)t->content
			&& *(size_t *)new_t->content == *(size_t *)f->content))
			return (TRUE);
		f = f->next;
		t = t->next;
	}
	return (FALSE);
}
