/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strenqu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:52:22 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 19:05:12 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Compare lexicographiquement s1 et s2 jusqu'a n caracteres maximum ou bien
** '\0' ait ete rencontre. Si les deux chaines sont egales, la fonction
** retourne 1, sinon 0.
*/

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2 || ft_strncmp(s1, s2, n) != 0)
		return (0);
	return (1);
}
