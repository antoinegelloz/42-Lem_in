/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:47:25 by ekelkel           #+#    #+#             */
/*   Updated: 2019/09/27 15:25:36 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_queue(t_queue *queue)
{
	free(queue->prev);
	free(queue->out);
	free(queue->array);
	free(queue);
	return ;
}
