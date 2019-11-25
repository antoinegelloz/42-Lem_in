/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:38:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/11/25 18:14:06 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t		update_edge_capacities(t_bfs *new_bfs, t_graph *graph)
{
  t_list	*curr;

  curr = NULL;
  curr = new_bfs->shortest_path;
  while (curr->next != NULL)
  {
    change_capacity(graph, curr, curr->next, DECREASE);
    change_capacity(graph, curr->next, curr, INCREASE);
    curr = curr->next;
  }
  return (SUCCESS);
}

t_list		*edmonds_karp(t_graph *graph)
{
  t_list	*aug_paths;
  t_bfs   *new_bfs;

  aug_paths = NULL;
  new_bfs = NULL;
  while (TRUE)
  {
    //ft_putendl("BFS");
    if ((new_bfs = bfs(graph)) == NULL)
      return (find_disjoint_paths(graph, aug_paths));
    ft_lstappend(&aug_paths, new_bfs->shortest_path);
    graph->paths_count++;
    update_edge_capacities(new_bfs, graph);
    free_bfs(new_bfs);
    //aug_paths = find_disjoint_paths(graph, aug_paths);
  }
  return (NULL);
}
