/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/29 10:28:37 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdio.h>

typedef struct	s_edge
{
	size_t			dest;
	size_t			capacity;
	struct s_edge	*next;
}				t_edge;

typedef struct	s_path
{
	size_t			value;
	struct s_path	*next;
}				t_path;

typedef struct	s_node
{
	int		index;
	int		x_coord;
	int		y_coord;
	int8_t	source;
	int8_t	sink;
	int8_t	bfs_marked;
	char	pad[1];
	char	*name;
	t_edge	*head;
}				t_node;

typedef struct	s_graph
{
	size_t	ants;
	size_t	size;
	t_node	*nodes;
}				t_graph;

typedef struct	s_parsing
{
	size_t	index;
	size_t	ants;
	ssize_t	source;
	ssize_t	sink;
	int8_t	is_prev_command;
	char	pad[7];
	t_list	*nodes;
	t_list	*x_coord;
	t_list	*y_coord;
	t_list	*from;
	t_list	*to;
	t_list	*file;
}				t_parsing;

typedef struct	s_bfs
{
	size_t		queue_front;
	size_t		queue_rear;
	size_t		queue_size;
	size_t		queue_capacity;
	ssize_t		*queue;
	ssize_t		*prev;
	t_list		*best_path;
}				t_bfs;

int8_t			parse_file(t_parsing *p);
int8_t			save_node(t_parsing *p, char *line);
int8_t			save_edge(t_parsing *p, char *line);
int8_t			is_ants(char *line);
int8_t			is_command(char *line);
int8_t			is_node(char *line);
int8_t			is_name_duplicate(t_parsing *p, char *new_name);
int8_t			is_coord_duplicate(t_parsing *p, int x, int y);
int8_t			is_edge_duplicate(t_parsing *p, t_list *new_from,
									t_list *new_to);
int8_t			is_edge(char *line);
int8_t			is_comment_or_false_command(char *line);
int8_t			check_int(char *nb, int8_t pos);

t_graph			*create_graph(t_parsing *p);
int8_t			create_edge(t_graph *graph, size_t src, size_t dest);

void			print_graph(t_graph *graph);
void			print_nodes_names(t_parsing *p);
void			print_coord_x(t_parsing *p);
void			print_coord_y(t_parsing *p);
void			print_edges(t_parsing *p);
void			print_file(t_parsing *p);
void			print_ssize_t(t_list *list);

int8_t			exit_parsing_error(t_parsing *p, char *line, char **tab);
void			free_p(t_parsing *p);
void			free_tab(char **tab);
void			free_graph(t_graph *graph);

t_list			*edmonds_karp(t_graph *graph);

t_bfs			*bfs(t_graph *graph);
t_bfs			*create_queue(t_graph *graph);
int8_t			enqueue(t_bfs *bfs, size_t index);
int8_t			dequeue(t_bfs *bfs);
int8_t			is_queue_full(t_bfs *bfs);
int8_t			is_queue_empty(t_bfs *bfs);
void			free_queue(t_bfs *bfs);

#endif
