/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/24 18:29:10 by agelloz          ###   ########.fr       */
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
	int8_t	source;
	int8_t	sink;
	t_edge	*head;
}				t_node;

typedef struct	s_graph
{
	size_t	ants;
	size_t	size;
	t_node	*array;
}				t_graph;

typedef struct	s_rooms
{
	int				x_coord;
	int				y_coord;
	char			*name;
	struct s_room	*next;
}				t_rooms;

t_list			*save_file(void);
int8_t			is_edge(char *line);
int8_t			is_node(char *line);
int8_t			is_comment_or_false_command(char *line);
int8_t			is_ants(char *line);
int8_t			is_command(char *line);
int8_t			check_nodes(t_graph *graph, t_list *file, size_t size);

t_graph			*create_graph(size_t size);
int8_t			add_one_edge(t_graph *graph, int src, int dest);

t_graph			*exit_graph_error(t_graph *graph, t_list *file);
t_list			*exit_file_error(t_list **file);
int8_t			exit_node_error(char **node_data);
void			free_graph(t_graph *graph);

t_graph			*edmonds_karp(t_graph *graph);

void			print_graph(t_graph *graph);

#endif
