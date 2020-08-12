/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:45:40 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/30 18:17:51 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne une chaine de caractere "fraiche"
** terminee par un '\0'. Chaque caractere de la chaine est initialise a '\0'.
** Si l'allocation echoue, la fonction renvoie NULL.
*/

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(str, 0, size + 1);
	return (str);
}
