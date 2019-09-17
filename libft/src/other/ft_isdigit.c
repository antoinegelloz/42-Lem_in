/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:15:52 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 19:16:45 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isdigit() function tests for a decimal digit character. Regardless of
** locale, this includes the following characters only: 0-9. The value of the
** argument must be representable as an unsigned char or the value of EOF.
** The isdigit() function return zero if the character tests false and return
** non-zero if the character tests true.
*/

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
