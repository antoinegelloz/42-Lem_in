/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:48:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 18:59:25 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applique la fonction f a chaque caractere de la chaine de caractere passee
** en parametre en precisant son index en premier argument. Chaque caractere
** est passe par adresse a la fonction f afin de pour etre modifie si
** necessaire.
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int i;

	i = 0;
	if (s && f)
		while (*s)
			f(i++, s++);
}
