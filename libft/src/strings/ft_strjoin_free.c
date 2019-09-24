/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:55:28 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/14 21:49:10 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne une chaîne de caractères
** “fraiche” terminée par un ’\0’ résultant de la concaténation
** de s1 et s2. Free s1. Si l’allocation echoue, la fonction renvoie NULL.
*/

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char *result;

	if (!s1 || !s2 || !(result = ft_strnew((ft_strlen(s1)
						+ ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcpy(result, s1);
	free(s1);
	ft_strcat(result, s2);
	return (result);
}
