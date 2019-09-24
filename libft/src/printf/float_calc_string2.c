/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_calc_string2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:03:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/06/27 13:50:54 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_check2(char **p1, char **p2, char **s1)
{
	*p1 = *p1 - 1;
	*p2 = *p2 - 1;
	while (**p1 >= **p2 && *p1 > *s1)
	{
		if (**p1 > **p2)
			break ;
		*p1 = *p1 - 1;
		*p2 = *p2 - 1;
	}
	if ((**p1 == **p2 && *p1 == *s1) || (**p1 < **p2 && *p1 >= *s1))
	{
		if (**p1 == **p2 && *p1 == *s1)
		{
			**s1 = '0';
			*s1 = *s1 + 1;
		}
		while (**s1 != 'u')
		{
			**s1 = 'u';
			*s1 = *s1 + 1;
		}
		return (0);
	}
	return (1);
}

int		ft_check(char *s1, char *s2, char *p1, char *p2)
{
	if (*s1 == 'u' || *s2 == 'u')
		return (0);
	while (*p1 != 'u' && *p2 != 'u')
	{
		p1++;
		p2++;
		if (*p1 == 'u' && *p2 != 'u')
		{
			while (*s1 != 'u')
				*s1++ = 'u';
			return (0);
		}
		if (*p1 == 'u' && *p2 == 'u')
		{
			if (ft_check2(&p1, &p2, &s1) == 0)
				return (0);
			break ;
		}
	}
	return (1);
}

void	ft_sub_str2(char **s1, char **s2, char **p1)
{
	while (**s2 != 'u' && **s1 != 'u' && (**s1 - **s2) < 0)
	{
		**s1 = (**s1 - **s2) + 58;
		*s2 = *s2 + 1;
		*s1 = *s1 + 1;
		if (**s1 != 'u')
		{
			*p1 = *s1;
			while (**p1 == '0')
			{
				**p1 = '9';
				*p1 = *p1 + 1;
			}
			**p1 = (**p1 - 1 >= '0') ? **p1 - 1 : 'u';
		}
	}
}

void	ft_sub_str(char *s1, char *s2)
{
	char *p1;
	char *p2;

	p1 = s1;
	p2 = s2;
	if (!ft_check(s1, s2, p1, p2))
		return ;
	while (*s2 != 'u')
	{
		if (*s2 != 'u' && *s1 != 'u' && (*s1 - *s2) < 0)
			ft_sub_str2(&s1, &s2, &p1);
		else
		{
			if (*s1 != 'u')
				*s1 = (*s1 - *s2 >= 0) ? (*s1 - *s2) + 48 : 'u';
			s2++;
			s1++;
		}
	}
	while (*s1 != 'u')
		s1++;
	s1--;
	while (*s1 == '0')
		*s1-- = 'u';
}
