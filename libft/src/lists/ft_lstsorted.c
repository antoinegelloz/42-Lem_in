/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:34:20 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 10:36:58 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsorted(t_list *list, int size, int (*cmp)(void *, void *))
{
	if (!list || !list->next || size == 0)
		return (1);
	if (cmp(list->content, list->next->content) > 0)
		return (ft_lstsorted(list->next, size - 1, cmp));
	return (0);
}
