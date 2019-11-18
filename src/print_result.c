/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:58:06 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/06 18:26:15 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t			init_lines(t_paths *paths, t_graph *graph)
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
	return (SUCCESS);
}

static void		print_first_ant(t_list **ants_pos, t_paths *paths,
		t_graph *graph, size_t i)
{
	if (paths->available[paths->ants_to_paths[i]] == TRUE)
	{
		ants_pos[i] = ants_pos[i]->next;
		if (ants_pos[i] != NULL && ants_pos[i]->next != NULL)
			paths->available[paths->ants_to_paths[i]] = FALSE;
		paths->n[paths->ants_to_paths[i]]--;
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
}

int8_t			print_lines(t_paths *paths, t_graph *graph)
{
	t_list	**ants_pos;
	ssize_t	*tmp_pos;
	size_t	i;

	if ((ants_pos = (t_list**)malloc(sizeof(t_list*) * graph->ants)) == NULL)
		return (FAILURE);
	i = 0;
	while (i < graph->ants)
	{
		ants_pos[i] = paths->array[paths->ants_to_paths[i]];
		i++;
	}
	while (paths->round < paths->output_lines)
	{
		if (!(tmp_pos = save_ants_pos(ants_pos, graph->ants)))
			return (FAILURE);
		print_round(paths, graph, ants_pos, tmp_pos);
		ft_putchar('\n');
		free(tmp_pos);
		tmp_pos = NULL;
		paths->round++;
	}
	free(ants_pos);
	ants_pos = NULL;
	return (SUCCESS);
}
