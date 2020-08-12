/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:12:07 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/07 17:13:13 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memmove() function copies len bytes from string src to string dst.
** The two strings may overlap; the copy is always done in a non-destructive
** manner.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (src == dst)
		return (dst);
	d = (char *)dst;
	s = (const char *)src;
	if (src > dst)
		dst = ft_memcpy(dst, src, len);
	else
	{
		d += len;
		s += len;
		while (len--)
			*--d = *--s;
	}
	return (dst);
}
