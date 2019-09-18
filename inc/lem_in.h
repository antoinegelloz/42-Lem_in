/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/18 13:28:45 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include "libft.h"

typedef struct	s_edge
{
	int				dest;
	int				capacity;
	struct s_edge	*next;
}				t_edge;

typedef struct	s_node
{
	int		index;
	int		source;
	int		sink;
	int		bfs_marked;
	char	*name;
	t_edge	*head;
}				t_node;

typedef struct	s_graph
{
	size_t	size;
	t_node	*array;
}				t_graph;

t_graph	*create_graph(size_t size);
int8_t	add_edge(t_graph *graph, int src, int dest);

t_graph	*exit_parse_error(void);
t_graph *exit_graph_error(void);
int8_t	exit_free_graph(t_graph *graph);

void	print_graph(t_graph *graph);

#endif
