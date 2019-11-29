/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:58:06 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/29 16:02:16 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			init_lines(t_paths *paths, t_graph *graph)
{
	size_t	i;
	size_t	tmp;

	paths->output_lines = ft_lstgetsize(paths->array[0]) - 1;
	i = 1;
	while (i < graph->paths_count)
	{
		tmp = ft_lstgetsize(paths->array[i]) - 1;
		if (tmp < paths->output_lines)
			paths->output_lines = tmp;
		i++;
	}
}

static void		print_first_ant(t_list **ants_pos, t_paths *paths,
								t_graph *graph, size_t i)
{
	if (paths->available[paths->ants_to_paths[i]] == TRUE)
	{
		if (ants_pos[i] != NULL)
			ants_pos[i] = ants_pos[i]->next;
		if (ants_pos[i] != NULL && ants_pos[i]->next != NULL)
			paths->available[paths->ants_to_paths[i]] = FALSE;
		paths->n[paths->ants_to_paths[i]]--;
		if (ants_pos[i] != NULL)
			ft_printf("L%d-%s", i + 1,
						graph->nodes[*(size_t *)ants_pos[i]->content].name);
	}
}

static void		print_moving_ant(t_list **ants_pos, t_paths *paths,
									t_graph *graph, size_t i)
{
	if (ants_pos[i] == paths->array[paths->ants_to_paths[i]]->next
					&& paths->n[paths->ants_to_paths[i]] > 0)
		paths->available[paths->ants_to_paths[i]] = TRUE;
	if (ants_pos[i] != NULL)
		ants_pos[i] = ants_pos[i]->next;
	if (ants_pos[i] != NULL)
		ft_printf("L%d-%s", i + 1,
					graph->nodes[*(size_t *)ants_pos[i]->content].name);
}

static void		print_round(t_paths *paths, t_graph *graph,
							t_list **ants_pos, ssize_t *tmp_pos)
{
	size_t	i;

	i = 0;
	while (i < graph->ants)
	{
		if (ants_pos[i] == paths->array[paths->ants_to_paths[i]])
			print_first_ant(ants_pos, paths, graph, i);
		else if (ants_pos[i] != NULL && ants_pos[i]->next != NULL)
			print_moving_ant(ants_pos, paths, graph, i);
		else if (ants_pos[i] != NULL && ants_pos[i]->next == NULL)
			ants_pos[i] = ants_pos[i]->next;
		if (i < graph->ants && ants_pos[i] != NULL)
		{
			if (ants_pos[i]->next == NULL)
				ants_pos[i] = ants_pos[i]->next;
			if (all_moved(ants_pos, tmp_pos, graph, paths) == FALSE)
				ft_putchar(' ');
		}
		i++;
	}
	ft_putchar('\n');
}

void			print_lines(t_paths *paths, t_graph *graph)
{
	t_list	*ants_pos[graph->ants];
	ssize_t	tmp_pos[graph->ants];
	size_t	i;
	size_t	round;

	i = -1;
	while (++i < graph->ants)
		ants_pos[i] = paths->array[paths->ants_to_paths[i]];
	round = 0;
	while (round++ < paths->output_lines)
	{
		i = 0;
		while (i < graph->ants)
		{
			if (ants_pos[i] != NULL)
				tmp_pos[i] = *(ssize_t *)ants_pos[i]->content;
			else
				tmp_pos[i] = -1;
			i++;
		}
		print_round(paths, graph, ants_pos, tmp_pos);
	}
}
