/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:03:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:34:17 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "printf_floats.h"

void	ft_ldouble(t_sp *sp, char *bin)
{
	int		exp;
	char	*ret;

	if (!(ret = ft_strnewu(17000)))
		return ;
	exp = ft_bin2dec(bin++, 15) - 16383;
	*ret = '0';
	ft_calc(bin, exp + 1, ret);
	ft_reverse(ret);
	ft_format(sp, ret, bin - 16);
	ft_strfree(&ret);
}

void	ft_double(t_sp *sp, char *bin)
{
	int		exp;
	char	*ret;

	if (!(ret = ft_strnewu(1077)))
		return ;
	exp = ft_bin2dec(bin++, 11) - 1023;
	*ret = '0';
	if (exp >= 0)
		ft_add_pos2power(ret, exp);
	else if (exp == -1023)
		exp++;
	else
		ft_add_neg2power(ret + 2, -exp);
	ft_calc(bin, exp, ret);
	ft_reverse(ret);
	ft_format(sp, ret, bin - 12);
	ft_strfree(&ret);
}

int		ft_check_binary(t_sp *sp, char *bin)
{
	int	i;
	int	exp_size;

	i = 1;
	if (sp->type_size == 8)
		exp_size = 15;
	else
		exp_size = 11;
	while (i < exp_size + 1)
		if (bin[i++] == '0')
			return (1);
	while (bin[i])
	{
		if (bin[i++] == '1')
		{
			ft_format(sp, "nan", bin);
			return (0);
		}
	}
	if (bin[0] == '1')
		ft_format(sp, "-inf", bin);
	else
		ft_format(sp, "inf", bin);
	return (0);
}

int		ft_get_binary(t_sp *sp, t_double d, char *bin)
{
	int	i;
	int	j;

	i = 0;
	j = 16 * sp->type_size - 1;
	if (sp->type_size == 8)
	{
		while (i < 64)
			bin[j--] = ((d.lb.mantissa >> i++) & 1) + 48;
		i = 0;
		while (i < 15)
			bin[j--] = ((d.lb.exp >> i++) & 1) + 48;
		bin[j--] = (d.lb.sign) + 48;
		return (ft_check_binary(sp, bin + 48));
	}
	else
	{
		while (i < 52)
			bin[j--] = ((d.b.mantissa >> i++) & 1) + 48;
		i = 0;
		while (i < 11)
			bin[j--] = ((d.b.exp >> i++) & 1) + 48;
		bin[j] = (d.b.sign) + 48;
		return (ft_check_binary(sp, bin));
	}
}

void	ft_print_float(t_sp *sp)
{
	t_double	d;
	char		*bin;

	if (!(bin = ft_strnewu(16 * sp->type_size)))
		return ;
	if (sp->type_size == 8)
	{
		d.ldbl = va_arg(sp->ap, long double);
		if (ft_get_binary(sp, d, bin))
			ft_ldouble(sp, bin + 63);
	}
	else
	{
		d.dbl = va_arg(sp->ap, double);
		if (ft_get_binary(sp, d, bin))
			ft_double(sp, bin + 11);
	}
	ft_strfree(&bin);
}
