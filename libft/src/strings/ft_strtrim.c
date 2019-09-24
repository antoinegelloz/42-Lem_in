/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:56:19 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/11 17:01:20 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne une copie de la chaîne
** passée en paramètre sans les espaces blancs au debut et à la
** fin de cette chaîne. On considère comme espaces blancs les
** caractères ’ ’, ’\n’ et ’\t’. Si s ne contient pas d’espaces
** blancs au début ou à la fin, la fonction renvoie une copie de
** s. Si l’allocation echoue, la fonction renvoie NULL.
*/

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int i;
	int j;

	if (!s)
		return (NULL);
	i = 0;
	while (s && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	j = ft_strlen(s) - 1;
	while (s && j > 0 && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	if (j == 0)
		return (ft_strdup(""));
	return ((char *)ft_strsub((const char *)s, (unsigned int)i,
			(size_t)(j - i + 1)));
}
