/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetmax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:09:22 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 14:24:52 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstgetmax(t_list *list, int size)
{
	int max;

	max = *(int *)list->content;
	while (list && size--)
	{
		if (*(int *)list->content > max)
			max = *(int *)list->content;
		list = list->next;
	}
	return (max);
}
