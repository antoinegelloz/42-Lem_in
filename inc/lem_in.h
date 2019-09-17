/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/17 12:12:38 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

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
	int		size;
	t_node	*array;
}				t_graph;

#endif
