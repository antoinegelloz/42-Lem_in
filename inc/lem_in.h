/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/24 11:08:19 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include "libft.h"

typedef struct	s_edge
{
	size_t			dest;
	size_t			capacity;
	struct s_edge	*next;
}				t_edge;

typedef struct	s_node
{
	size_t	index;
	int8_t	source;
	int8_t	sink;
	int8_t	bfs_marked;
	char	pad[5];
	t_edge	*head;
	char	*name;
}				t_node;

typedef struct	s_graph
{
	size_t	ants;
	size_t	size;
	t_node	*array;
}				t_graph;

t_list			*save_file(void);
int8_t			is_tunnel(char *line);
int8_t			is_room(char *line);
int8_t			is_comment_or_false_command(char *line);
int8_t			is_ants(char *line);
int8_t			is_command(char *line);

t_graph			*create_graph(size_t size);
int8_t			add_edge(t_graph *graph, int src, int dest);

t_graph			*exit_graph_error(t_graph *graph, t_list *file);
t_list			*exit_file_error(t_list **file);
void			free_graph(t_graph *graph);

t_graph			*edmonds_karp(t_graph *graph);

void			print_graph(t_graph *graph);

#endif
