/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:58:17 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/09 14:42:33 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Prend en paramètre l’adresse d’un pointeur sur un maillon et libère la
** mémoire du contenu de ce maillon avec la fonction del passée en paramètre
** puis libère la mémoire du maillon en lui même avec free(3). La mémoire du
** champ next ne doit en aucun cas être libérée. Pour terminer, le pointeur
** sur le maillon maintenant libéré doit être mis à NULL (de manière similaire
** à la fonction ft_memdel de la partie obligatoire).
*/

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	if (!alst || !del)
		return ;
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
	return ;
}
