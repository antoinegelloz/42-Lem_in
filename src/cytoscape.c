/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cytoscape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:01:09 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/03 14:11:28 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>
#include <sys/types.h>

int8_t	cytoscape_visualizer(t_graph *graph, t_paths *paths)
{
	FILE	*file;
	size_t	i;
	size_t	j;
	t_edge	*curr_edge;
	char 	*prefix;
	char 	*suffix;
	int		position;

	i = 0;
	file = fopen("cytoscape/data.json", "w");
	fprintf(file, "{ \"nodes\": [\n");
	prefix = "{ \"data\": { \"id\": \"";
	suffix = "\" } },\n";
	while (i < graph->size)
	{
		fprintf(file, "%s", prefix);
		fprintf(file, "%s", graph->nodes[i].name);
		if (graph->nodes[i].source == 1)
			fprintf(file, "\", \"start\": \"yes\", \"type\": \"start");
		else if (graph->nodes[i].sink == 1)
			fprintf(file, "\", \"end\": \"yes\", \"type\": \"end");
		fprintf(file, "%s", suffix);
		i++;
	}
	fseeko(file, -2, SEEK_END);
	position = ftello(file);
	ftruncate(fileno(file), position);
	fprintf(file, "\n], \"edges\": [\n");
	i = 0;
	j = 0;
	while (i < graph->size)
	{
		curr_edge = graph->nodes[i].head;
		while (curr_edge)
		{
			fprintf(file, "%se%zd\", \"source\": \"%s\", \"target\": \"%s%s", prefix, j, graph->nodes[i].name, graph->nodes[curr_edge->dest].name, suffix);
			curr_edge = curr_edge->next;
			j++;
		}
		i++;
	}
	fseeko(file, -2, SEEK_END);
	position = ftello(file);
	ftruncate(fileno(file), position);
	fprintf(file, "\n] }\n");
	system("if ! ps aux | grep -v grep | grep 'php -S localhost:8000' &>/dev/null; then php -S localhost:8000 &>/dev/null & fi");
	system("open -a \"Google Chrome\" http://localhost:8000/cytoscape/");
	return (SUCCESS);
}
