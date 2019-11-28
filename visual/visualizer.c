/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:01:09 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/28 13:05:16 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int8_t	dump_path(FILE *file, t_paths *paths, size_t i, size_t path_id, t_graph *graph)
{
	t_list *curr;

	fprintf(file, "{ \"id\": %zd, \"ants\": %zd, \"nodes\": [",
			path_id, paths->n[i]);
	curr = paths->array[i];
	while (curr)
	{
		fprintf(file, "\"%s\"", graph->nodes[*(size_t *)curr->content].name);
		curr = curr->next;
		if (curr)
			fprintf(file, ", ");
	}
	fprintf(file, "] },\n");
	return (SUCCESS);
}

int8_t	visualizer(t_graph *graph, t_paths *paths)
{
	FILE	*file;
	size_t	i;
	size_t	j;
	t_edge	*curr_edge;
	char 	*prefix;
	char 	*suffix;
	int		position;

	i = 0;
	file = fopen("visual/data.json", "w");
	fprintf(file, "{\n\"nodes\": \n[");
	prefix = "{ \"data\": { \"id\": \"";
	suffix = "\" } },\n";
	while (i < graph->size)
	{
		fprintf(file, "%s", prefix);
		fprintf(file, "%s", graph->nodes[i].name);
		if (graph->nodes[i].source == 1)
			fprintf(file, "\", \"type\": \"start");
		else if (graph->nodes[i].sink == 1)
			fprintf(file, "\", \"type\": \"end");
		fprintf(file, "%s", suffix);
		i++;
	}
	fseeko(file, -2, SEEK_END);
	position = ftello(file);
	ftruncate(fileno(file), position);
	fprintf(file, "],\n\"edges\":\n[");
	i = 0;
	j = 0;
	while (i < graph->size)
	{
		curr_edge = graph->nodes[i].head;
		while (curr_edge)
		{
			fprintf(file, "%se%zd\", \"source\": \"%s\", \"target\": \"%s%s",
					prefix, j, graph->nodes[i].name,
					graph->nodes[curr_edge->dest].name, suffix);
			curr_edge = curr_edge->next;
			j++;
		}
		i++;
	}
	fseeko(file, -2, SEEK_END);
	position = ftello(file);
	ftruncate(fileno(file), position);
	fprintf(file, "],\n\"paths\":\n[");
	i = 0;
	j = 0;
	while (i < graph->paths_count)
	{
		//if (paths->n[i] > 0)
		//{
			dump_path(file, paths, i, j, graph);
			j++;
		//}
		i++;
	}
	fseeko(file, -2, SEEK_END);
	position = ftello(file);
	ftruncate(fileno(file), position);
	fprintf(file, "],\n\"ants\": %zu,\n", graph->ants);
	fprintf(file, "\"paths_used\": %zu,\n", paths->paths_used);
	fprintf(file, "\"paths_count\": %zu\n", graph->paths_count);
	fprintf(file, "}\n");
	system("if ! ps aux | grep -v grep | grep 'php -S localhost:8000' &>/dev/null; then php -S localhost:8000 &>/dev/null & fi");
	system("open -a \"Google Chrome\" http://localhost:8000/visual/");
	return (SUCCESS);
}
