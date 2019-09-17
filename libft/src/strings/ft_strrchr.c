/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:13:27 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/07 18:48:01 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strrchr() function locates the last occurence of c (converted to a char)
** in the string pointed to by s. The terminating null character is considered
** to be part of the string; therefore if c is '/0', the functions locate the
** terminating '\0'. The function strchr() returns a pointer to the located
** character, or NULL if the character does not appear in the string.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *last;

	last = NULL;
	while (1)
	{
		if (*s == c)
			last = (char *)s;
		if (*s == 0)
			return (last);
		s++;
	}
}
