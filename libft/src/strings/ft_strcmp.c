/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:22:06 by agelloz           #+#    #+#             */
/*   Updated: 2019/07/19 14:45:37 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strcmp() function lexicographically compare the null-terminated
** strings s1 and s2. It returns an integer greater than, equal to, or
** less than 0, according as the string s1 is greater than, equal to or
** less than the string s2. The comparison is done using unsigned characters,
** so that '\200' is greater than '\0'.
*/

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
