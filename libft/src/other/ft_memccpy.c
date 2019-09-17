/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:11:52 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/10 14:54:21 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** THe memccpy() function copies bytes from string src to string dst. If the
** the character c (as converted to an unsigned char) occurs in the string src,
** the copy stops and a pointer to the byte after the copy of c in the string
** dst in returned. Otherwise, n bytes are copied, and a NULL pointer is
** returned.
*/

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void *p;

	p = ft_memchr(src, c, n);
	if (p != NULL)
		return (ft_memcpy(dst, src, p - src + 1) + (p - src + 1));
	ft_memcpy(dst, src, n);
	return (NULL);
}
