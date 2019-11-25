/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_disjoint_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:12:57 by ekelkel           #+#    #+#             */
/*   Updated: 2019/11/25 17:50:24 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*rebuild_aug_paths(t_graph *graph)
{
  t_list		*new_aug_paths;
  t_list		*tmp;
  t_edge		*neighbours;
  t_edge		*neighbours2;
  size_t		node;

  new_aug_paths = NULL;
  tmp = NULL;
  node = graph->source;
  neighbours = graph->nodes[graph->source].head;
  while (neighbours != NULL)
  {
    if (neighbours->capacity == 0)
    {
      tmp = ft_lstnew(&graph->source, sizeof(size_t));
      ft_lstappend(&new_aug_paths, tmp);
      node = neighbours->dest;
      tmp = ft_lstnew(&node, sizeof(size_t));
      ft_lstappend(&new_aug_paths, tmp);
      neighbours2 = graph->nodes[node].head;
      while (neighbours2 && node != graph->sink)
      {
        if (neighbours2->capacity == 0)
        {
          node = neighbours2->dest;
          tmp = ft_lstnew(&node, sizeof(size_t));
          ft_lstappend(&new_aug_paths, tmp);
          neighbours2 = graph->nodes[node].head;
        }
        else
          neighbours2 = neighbours2->next;
      }
    }
    neighbours = neighbours->next;
  }
  return (new_aug_paths);
}

/*int8_t	is_new_solution_better(t_bfs *new_bfs, t_list *aug_paths, t_graph *graph)
{
  t_paths *paths;
  size_t old_output_lines;
  size_t new_output_lines;
  size_t  i;

  old_output_lines = 0;
  new_output_lines = 0;
  i = 0;
  paths = NULL;
  if ((paths = init_output(graph, paths, aug_paths)) == NULL)
    return (FAILURE);
  init_lines(paths, graph);
  while (is_solution_found(paths, graph) == FALSE)
  {
    i = 0;
    while (i < graph->paths_count)
      paths->n[i++] = 0;
    paths->output_lines++;
  }
  // To do:
  // compute old and new output_lines
  // if (new_output_lines > old_output_lines)
  //	return (FALSE);
  return (TRUE);
}*/

size_t	is_on_path(size_t node, t_list *path, t_graph *graph)
{
  t_list	*curr;

  curr = path;
  while (curr != NULL && *(size_t *)curr->content != graph->sink)
  {
    if (*(size_t *)curr->content == node
        && node != graph->source && node != graph->sink)
      return (TRUE);
    curr = curr->next;
  }
  return (FALSE);
}

t_bfs   *bfs_disjoint_paths(t_graph *graph, t_list *path)
{
  t_bfs	  *new_bfs;
  t_edge	*neighbours;
  t_edge	*neighbours2;
  size_t	node;
  int8_t	node_on_path;

  neighbours = NULL;
  new_bfs = init_bfs(graph);
  while (is_queue_empty(new_bfs) == FALSE)
  {
    node = dequeue(new_bfs);
    node_on_path = is_on_path(node, path, graph);
    neighbours = graph->nodes[node].head;
    while (neighbours != NULL)
    {
      if (graph->nodes[neighbours->dest].already_enqueued == FALSE)
      {
        if (node_on_path == FALSE && node != graph->sink)
        {
          if (is_on_path(neighbours->dest, path, graph) == TRUE)
          {
            new_bfs->prev[neighbours->dest] = node;
            graph->nodes[neighbours->dest].bfs_marked = TRUE;
            graph->nodes[neighbours->dest].already_enqueued = TRUE;
            neighbours2 = graph->nodes[neighbours->dest].head;
            while (neighbours2)
            {
              if (neighbours2->capacity == 2 && is_on_path(neighbours2->dest, path, graph) == TRUE)
                enqueue(neighbours->dest, neighbours2->dest, graph, new_bfs);
              neighbours2 = neighbours2->next;
            }
          }
          else if (graph->nodes[neighbours->dest].bfs_marked == FALSE)
            enqueue(node, neighbours->dest, graph, new_bfs);
        }
        else if (node_on_path == TRUE
            && ((neighbours->capacity == 2 && neighbours->dest != graph->source)
              ||  neighbours->capacity == 1))
          enqueue(node, neighbours->dest, graph, new_bfs);
      }
      neighbours = neighbours->next;
    }
  }
  return (reconstruct_path(new_bfs, graph));
}

t_list *edmonds_disjoint_paths(t_graph *graph, t_list *aug_paths, t_list *path)
{
  t_bfs	  *new_bfs;

  new_bfs = NULL;
  if ((new_bfs = bfs_disjoint_paths(graph, path)) == NULL)
    return (aug_paths);
  //if (is_new_solution_better(new_bfs, aug_paths, graph) == FALSE)
    //return (aug_paths);
  graph->paths_count++;
  update_edge_capacities(new_bfs, graph);
  ft_lstdel(&aug_paths, ft_delcontent);
  aug_paths = rebuild_aug_paths(graph);
  free_bfs(new_bfs);
  return (aug_paths);
}

t_list  *get_next_path(t_list *path, t_graph *graph)
{
  t_list  *next_path;

  next_path = path;
  while (next_path->next != NULL &&
      *(size_t *)next_path->next->content != graph->source)
    next_path = next_path->next;
  next_path = next_path->next;
  return (next_path);
}

t_list *find_disjoint_paths(t_graph *graph, t_list *aug_paths)
{
  t_list  *path;
  t_list  *new_aug_paths;
  size_t  prev_paths_count;

  path = aug_paths;
  new_aug_paths = aug_paths;
  while (path != NULL)
  {
    //ft_putendl("\npath:");
    //print_ssize_t(path);
    prev_paths_count = graph->paths_count;
    new_aug_paths = edmonds_disjoint_paths(graph, new_aug_paths, path);
    if (prev_paths_count == graph->paths_count)
    {
      if ((path = get_next_path(path, graph)) == NULL)
        return (new_aug_paths);
    }
    else // start again from first path
      path = new_aug_paths;
    //sleep(1);
  }
  return (new_aug_paths);
}
