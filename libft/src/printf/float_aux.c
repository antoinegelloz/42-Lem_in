/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:34:25 by agelloz           #+#    #+#             */
/*   Updated: 2019/06/27 13:44:45 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdlib.h>

void	ft_strfree(char **s)
{
	if (*s && s)
	{
		free(*s);
		*s = NULL;
	}
}

char	*ft_strnewu(size_t size)
{
	char *s;
	char *p;

	if (!(s = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	p = s;
	while (size--)
		*p++ = 'u';
	*p = '\0';
	return (s);
}

int		ft_bin2dec(char *bin, int len)
{
	int ret;
	int power;
	int digit;

	ret = 0;
	power = 1;
	while (len--)
	{
		digit = *bin - 48;
		ret += digit * power;
		power *= 2;
		bin--;
	}
	return (ret);
}

void	ft_reverse(char *ret)
{
	char tmp;
	char *p;

	p = ret;
	while (*(p + 1) != '.' && *(p + 1) != 'u' && *(p + 1) != '\0')
		p++;
	if (*(p + 1) == 'u')
		*(p + 1) = '.';
	while (*ret != 'u' && ret < p)
	{
		if (*p != *ret)
		{
			tmp = *ret;
			*ret = *p;
			*p = tmp;
		}
		ret++;
		p--;
	}
}
