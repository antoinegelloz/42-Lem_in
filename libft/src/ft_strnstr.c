/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:08:23 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/08 11:38:41 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strnstr() function locates the first occurence of the null-terminated
** string needle in the null-terminated string haystack, where not more than
** len characters are searched. Characters that appear after a '\0' character
** are not searched. Since the strnstr() function is a FreeBSD specific API,
** it should only be used when portability is not a concern.
** If needle is an empty string haystack is returned; if needle occurs nowhere
** in haystack, NULL is returned; otherwise a pointer to the first character of
** the first occurence of needle is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!(needle[j]))
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while ((haystack[i + j] == needle[j]) && needle[j]
					&& (i + j) < len)
			{
				j++;
				if (!(needle[j]))
					return ((char*)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}
