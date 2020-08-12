/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:20:41 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 19:10:46 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The tolower() function converts an upper-case letter to the corresponding
** lower-case letter. The argument must be representable as an unsigned char
** or the value of EOF.
** If the argument is an upper-case letter, the tolower() function returns the
** corresponding lower-case letter if there is one; otherwise, the argument is
** returned unchanged.
*/

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
