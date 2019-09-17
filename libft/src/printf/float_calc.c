/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:03:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:30:06 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "printf_floats.h"
#include "libft.h"

void	ft_add_pos2power(char *ret, int exp)
{
	char *pos2power;

	if (!(pos2power = ft_strnewu(5000)))
		return ;
	pos2power[0] = '1';
	while (exp-- > 0)
		ft_double_str(pos2power);
	if (exp == -1)
		ft_add_str(pos2power, ret);
}

void	ft_add_neg2p2(char *num, char *neg2power, char *pos2power, char *tmp)
{
	char	*pnum;
	int		digit;

	num[0] = '1';
	while (!(num[0] == '0' && num[1] == 'u'))
	{
		pnum = num;
		while (*pnum != 'u')
			pnum++;
		while (pnum != num && --pnum >= num)
			*(pnum + 1) = *pnum;
		*pnum = '0';
		digit = 0;
		if (!(tmp = ft_strdup(num)))
			return ;
		while (tmp[0] != 'u')
		{
			ft_sub_str(tmp, pos2power);
			digit = (*tmp != 'u') ? digit + 1 : digit;
		}
		*neg2power++ = digit + 48;
		while (digit-- > 0)
			ft_sub_str(num, pos2power);
		ft_strfree(&tmp);
	}
}

void	ft_add_neg2power(char *ret, int exp)
{
	char	*neg2power;
	char	*pos2power;
	char	*num;
	char	*tmp;

	if (!(pos2power = ft_strnewu(5000)))
		return ;
	pos2power[0] = '1';
	while (exp-- > 0)
	{
		if (!(tmp = ft_strdup(pos2power)))
			return ;
		ft_add_str(tmp, pos2power);
		ft_strfree(&tmp);
	}
	if (!(num = ft_strnewu(5000))
		|| !(neg2power = ft_strnewu(17000)))
		return ;
	ft_add_neg2p2(num, neg2power, pos2power, tmp);
	ft_add_str_neg2power(neg2power, ret);
	ft_strfree(&num);
	ft_strfree(&neg2power);
	ft_strfree(&pos2power);
}

void	ft_calc(char *bin, int exp, char *ret)
{
	char	*p;

	while (*bin)
	{
		exp--;
		if ((*(ret + 1) == 'u' && exp < 0) || exp == 0)
		{
			p = ret;
			while (*p != 'u')
				p++;
			*p = '.';
		}
		if (*bin == '1' && exp >= 0)
			ft_add_pos2power(ret, exp);
		else if (*bin == '1' && exp < 0)
			ft_add_neg2power(p + 1, -exp);
		bin++;
	}
}
