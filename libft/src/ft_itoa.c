/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:44 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/10 15:40:22 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne une chaîne de caractères
** “fraiche” terminée par un ’\0’ représentant l’entier n passé
** en paramètre. Les nombres négatifs doivent être gérés.
** Si l’allocation échoue, la fonction renvoie NULL.
*/

#include "libft.h"

static int	ft_intlen(int n)
{
	int len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*s;

	if (!(s = ft_strnew(ft_intlen(n))))
		return (NULL);
	i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		if (n == -2147483648)
		{
			s[i++] = '2';
			n = -147483648;
		}
		n = -n;
	}
	if (n == 0)
		s[i++] = '0';
	while (n > 0)
	{
		s[(ft_intlen(n)) + i - 1] = n % 10 + 48;
		n /= 10;
	}
	return (s);
}
