/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:15:42 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 18:42:28 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isalpha() function tests for any character for which isupper(3) or
** islower(3) is true. The value of the argument must be representable as
** an unsigned char or the value of EOF.
** The isalpha() function returns 0 if the character tests false and returns
** non-zero if the character tests true.
*/

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
