/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:09:22 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:07 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstgetsize(t_list *list)
{
	t_list *curr;
	size_t size;

	size = 0;
	curr = list;
	while (curr)
	{
		curr = curr->next;
		size++;
	}
	return (size);
}
