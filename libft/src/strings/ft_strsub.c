/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:54:36 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/30 17:54:48 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne la copie "fraiche" d'un troncon de
** la chaine de caracteres passee en parametre. Le troncon commence a
** l'index start et a pour longueur len. Si start et len ne designent pas un
** troncon de chaine valide, le comportement est indetermine. Si l'allocation
** echoue, la fonction renvoie NULL.
*/

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s)
		return (NULL);
	if (!(result = ft_strnew(len)))
		return (NULL);
	result = ft_strncpy(result, (s + start), len);
	return (result);
}
