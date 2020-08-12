/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:12:23 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/07 17:21:30 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memchr() function locates the first occurence of c (converted to an
** unsigned char) in string s. The memchr() function returns a pointer to
** the byte located, or NULL if no such byte exists within n bytes.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ps;

	ps = (unsigned char*)s;
	while (ps && n-- > 0)
	{
		if (*ps == (unsigned char)c)
			return ((void*)ps);
		ps++;
	}
	return (NULL);
}
