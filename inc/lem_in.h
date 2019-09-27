/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/27 12:20:34 by agelloz          ###   ########.fr       */
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
	size_t	node_index;
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

typedef struct	s_queue
{
	int			front;
	int			rear;
	unsigned	size;
	unsigned	capacity;
	int			*array;
	ssize_t		*out;
	ssize_t		*prev;
}				t_queue;

int8_t			parse_file(t_parsing *p);
int8_t			save_node(t_parsing *p, char *line);
int8_t			save_edge(t_parsing *p, char *line);
int8_t			is_ants(char *line);
int8_t			is_command(char *line);
int8_t			is_node(char *line);
int8_t			is_name_duplicate(t_parsing *p, char *new_name);
int8_t			is_coord_duplicate(t_parsing *p, int x, int y);
int8_t			is_edge(char *line);
int8_t			is_comment_or_false_command(char *line);
int8_t			check_int(char *nb, int8_t pos);

t_graph			*create_graph(size_t size);
int8_t			create_edge(t_graph *graph, size_t src, size_t dest);

void			print_graph(t_graph *graph);
void			print_nodes_names(t_parsing *p);
void			print_coord_x(t_parsing *p);
void			print_coord_y(t_parsing *p);
void			print_edges(t_parsing *p);
void			print_file(t_parsing *p);

int8_t			exit_parsing_error(t_parsing *p, char *line, char **tab);
int8_t			free_p(t_parsing *p);
void			free_graph(t_graph *graph);
void			free_tab(char **tab);

int8_t			edmonds_karp(t_graph *graph);
t_queue			*create_queue(size_t capacity);
int 			isFull(t_queue *queue);
int 			isEmpty(t_queue *queue);
void 			enqueue(t_queue *queue, int data);
int				dequeue(t_queue *queue);
void			get_queue(t_graph *graph);

#endif
