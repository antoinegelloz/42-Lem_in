/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:01:09 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/29 18:26:59 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int8_t	dump_path(FILE *file, t_paths *paths, size_t path_id, t_graph *graph)
{
	t_list *curr;

	fprintf(file, "{ \"id\": %zd, \"ants\": %zd, \"nodes\": [",
			path_id, paths->n[path_id]);
	curr = paths->array[path_id];
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

void	remove_coma(FILE *file)
{
	int		position;

	fseeko(file, -2, SEEK_END);
	position = ftello(file);
	ftruncate(fileno(file), position);
}

void	print_paths(FILE *file, t_graph *graph, t_paths *paths)
{
	size_t	i;

	i = 0;
	while (i < graph->paths_count)
	{
		dump_path(file, paths, i, graph);
		i++;
	}
	remove_coma(file);
	fprintf(file, "],\n\"ants\": %zu,\n", graph->ants);
	fprintf(file, "\"paths_count\": %zu\n", graph->paths_count);
	fprintf(file, "}\n");
}

void	print_edges(FILE *file, t_graph *graph, t_paths *paths, char *prefix)
{
	size_t	i;
	size_t	j;
	t_edge	*curr_edge;

	remove_coma(file);
	fprintf(file, "],\n\"edges\":\n[");
	i = 0;
	j = 0;
	while (i < graph->size)
	{
		curr_edge = graph->nodes[i].head;
		while (curr_edge)
		{
			fprintf(file, "%se%zd\",\"source\":\"%s\",\"target\":\"%s\"}},\n",
					prefix, j, graph->nodes[i].name,
					graph->nodes[curr_edge->dest].name);
			curr_edge = curr_edge->next;
			j++;
		}
		i++;
	}
	remove_coma(file);
	fprintf(file, "],\n\"paths\":\n[");
	print_paths(file, graph, paths);
}

int8_t	visualizer(t_graph *graph, t_paths *paths)
{
	FILE	*file;
	char	*prefix;
	char	*suffix;
	size_t	i;

	i = 0;
	file = fopen("visual/data.json", "w");
	fprintf(file, "{\n\"nodes\": \n[");
	prefix = "{ \"data\": { \"id\": \"";
	suffix = "\"}},\n";
	while (i < graph->size)
	{
		fprintf(file, "%s%s", prefix, graph->nodes[i].name);
		if (graph->nodes[i].source == 1)
			fprintf(file, "\", \"type\": \"start");
		else if (graph->nodes[i].sink == 1)
			fprintf(file, "\", \"type\": \"end");
		fprintf(file, "%s", suffix);
		i++;
	}
	print_edges(file, graph, paths, prefix);
	system("if ! ps aux | grep -v grep | grep 'php -S localhost:8000' \
			&>/dev/null; then php -S localhost:8000 &>/dev/null & fi");
	system("open -a \"Google Chrome\" http://localhost:8000/visual/");
	return (SUCCESS);
}
