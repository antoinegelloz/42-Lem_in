/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:08:23 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/05 23:02:00 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strlcat() function concatenates strings. Designed to be safer,
** more consistent, and less error prone replacement for strncat(3). Unlike
** this function, strlcat() take the full size of the buffer (not just the
** length) and guarantee to NUL-terminate the result (as long as size is larger
** than 0 or as long as there is at least one byte free in dst). Note than a
** byte for the NUL should be included in size. Also note that strlcat() only
** operate on true ''C'' strings. This means that both src and dst must be
** NUL-terminated. The strlcat(0 function appends the NUL-terminated string
** src to the end of dsl. It will append atmost size - strlen(dst) - 1 bytes,
** NUL-terminating the result. The source and destination strings should not
** overlap, as the behavior is undefined.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*odst;
	const char	*osrc;
	size_t		bytes_left;
	size_t		dlen;

	odst = dst;
	osrc = src;
	bytes_left = size;
	while (bytes_left-- != 0 && *dst != '\0')
		dst++;
	dlen = dst - odst;
	bytes_left = size - dlen;
	if (bytes_left-- == 0)
		return (dlen + ft_strlen(src));
	while (*src != '\0')
	{
		if (bytes_left != 0)
		{
			*dst++ = *src;
			bytes_left--;
		}
		src++;
	}
	*dst = '\0';
	return (dlen + (src - osrc));
}
