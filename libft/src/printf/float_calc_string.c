/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_calc_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:03:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/06/27 13:50:23 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_add_str(char *s1, char *s2)
{
	char *ps2;

	while (*s1 && *s1 != 'u')
	{
		if (*s1 != 'u' && *s2 != 'u' && ((*s1 - 48) + (*s2 - 48)) >= 10)
		{
			while (*s1 && *s2 && *s1 != 'u' && ((*s1 - 48) + (*s2 - 48)) >= 10)
			{
				*s2 = (*s1 - 48) + (*s2 - 48) + 38;
				s1++;
				s2++;
				ps2 = s2;
				while (*ps2 && *ps2 == '9')
					*ps2++ = '0';
				*ps2 = (*ps2 == 'u') ? '1' : *ps2 + 1;
			}
		}
		else
		{
			*s2 = (*s2 == 'u') ? *s1 : *s2 + (*s1 - 48);
			s1++;
			s2++;
		}
	}
}

void	ft_add_str_neg2power(char *neg2power, char *ret)
{
	char *first;

	first = neg2power;
	while (*(neg2power + 1) != 'u' && *(neg2power++ + 1))
		ret++;
	while (neg2power >= first)
	{
		if (*ret != 'u' && ((*neg2power - 48) + (*ret - 48) >= 10))
		{
			while ((*neg2power - 48) + (*ret - 48) >= 10)
			{
				*ret = (*neg2power - 48) + (*ret - 48) + 38;
				ret--;
				*ret = *ret + 1;
				neg2power--;
			}
		}
		else
		{
			*ret = (*ret == 'u') ? *neg2power : *ret + (*neg2power - 48);
			neg2power--;
			ret--;
		}
	}
}

void	ft_double_str2(char **s, int *ret)
{
	while ((**s != 'u' && **s + (**s - 48) + *ret > '9')
			|| (**s == 'u' && *ret > 0))
	{
		if (**s != 'u' && **s + (**s - 48) + *ret > '9')
		{
			**s = (**s - 48) + (**s - 48) + 38 + *ret;
			if (*ret == 0)
				*ret += 1;
		}
		else if (*ret > 0 && **s == 'u')
		{
			**s = *ret + 48;
			*ret -= 1;
		}
		*s += 1;
		if (*ret > 0 && **s == 'u')
		{
			**s = '1';
			*s += 1;
			*ret -= 1;
		}
	}
}

void	ft_double_str(char *s)
{
	int ret;

	ret = 0;
	while (ret != 0 || *s != 'u')
	{
		if (*s + (*s - 48) + ret <= '9')
		{
			if (ret > 0)
			{
				*s = (*s - 48) + (*s - 48) + 48 + ret;
				ret = 0;
			}
			else
				*s = (*s - 48) + (*s - 48) + 48;
			s++;
		}
		ft_double_str2(&s, &ret);
	}
}
