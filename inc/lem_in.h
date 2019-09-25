/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/25 17:54:53 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <limits.h>

typedef struct	s_edge
{
	size_t			dest;
	size_t			capacity;
	struct s_edge	*next;
}				t_edge;

typedef struct	s_node
{
	int		x_coord;
	int		y_coord;
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

typedef struct	s_parsing
{
	size_t	room_index;
	size_t	ants;
	size_t	size;
	int8_t	is_prev_command;
	int8_t	is_start;
	int8_t	is_end;
	char	pad[5];
	t_list	*rooms;
	t_list	*x_coord;
	t_list	*y_coord;
	t_list	*file;
}				t_parsing;


int8_t			is_edge(char *line);
int8_t			is_node(char *line);
int8_t			is_comment_or_false_command(char *line);
int8_t			is_ants(char *line);
int8_t			is_command(char *line);

t_graph			*create_graph(size_t size);
int8_t			create_edge(t_graph *graph, int src, int dest);

int8_t			exit_parsing_error(t_parsing *p);
void			free_graph(t_graph *graph);

int8_t			edmonds_karp(t_graph *graph);

void			print_graph(t_graph *graph);

#endif
