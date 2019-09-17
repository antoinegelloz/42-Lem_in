/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:47:10 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 18:57:29 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Assigne la valeur '\0' a tous les caracteres de la chaine passee
** en parametre.
*/

#include "libft.h"

void	ft_strclr(char *s)
{
	if (s)
		ft_bzero((void*)s, ft_strlen(s));
}
