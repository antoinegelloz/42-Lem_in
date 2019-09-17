/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:16:23 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 18:43:13 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isascii() function test for an ASCII character, which is any character
** between 0 and octal 0177 inclusive.
*/

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
