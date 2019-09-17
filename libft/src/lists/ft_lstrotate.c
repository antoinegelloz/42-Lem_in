/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 09:29:41 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 09:29:46 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrotate(t_list **alst)
{
	t_list	*current;
	t_list	*first;

	first = *alst;
	*alst = first->next;
	current = first;
	while (current->next)
		current = current->next;
	current->next = first;
	first->next = NULL;
}
