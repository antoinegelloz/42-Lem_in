/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:43:15 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/11 17:13:03 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Prend en paramètre l’adresse d’un pointeur sur un maillon et libère la
** mémoire de ce maillon et celle de tous ses successeurs l’un après l’autre
** avec del et free(3). Pour terminer, le pointeur sur le premier maillon
** maintenant libéré doit être mis à NULL (de manière similaire à la fonction
** ft_memdel de la partie obligatoire).
*/

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (*alst)
	{
		ft_lstdel(&(*alst)->next, del);
		ft_lstdelone(alst, del);
	}
}
