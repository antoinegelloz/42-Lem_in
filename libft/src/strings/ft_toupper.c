/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:20:41 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 19:11:46 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The toupper() function converts an lower-case letter to the corresponding
** upper-case letter. The argument must be representable as an unsigned char
** or the value of EOF. If the argument is an lower-case letter, the toupper()
** function returns the corresponding upper-case letter if there is one;
** otherwise, the argument is returned unchanged.
*/

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
