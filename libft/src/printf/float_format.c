/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:03:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/10 11:19:53 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_special_values(t_sp *sp, char *ret)
{
	if (*ret < '0' || *ret > '9')
	{
		sp->output_size = (*ret == '-') ? 4 : 3;
		sp->right_spaces = (sp->left_align) ? sp->min_width
			- sp->output_size : 0;
		sp->left_spaces = (!sp->left_align) ? sp->min_width
			- sp->output_size : 0;
		ft_print_left_spaces(sp);
		if (*ret == 'n')
			ft_buffer(sp, "nan", 3);
		if (*ret == '-')
			ft_buffer(sp, "-inf", 4);
		if (*ret == 'i')
			ft_buffer(sp, "inf", 3);
		ft_print_right_spaces(sp);
		return (1);
	}
	return (0);
}

void	ft_calc_format(t_sp *sp, char *bin)
{
	if (sp->left_align == 0 && sp->zero != 0)
		sp->zeros = sp->min_width - sp->output_size - sp->precision;
	sp->zeros = (sp->zeros < 0) ? 0 : sp->zeros;
	sp->right_spaces = (sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size - sp->precision - 1 : 0;
	sp->left_spaces = (!sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size - sp->precision - 1 : 0;
	ft_print_left_spaces(sp);
	if (bin[0] == '1')
		ft_buffer(sp, "-", 1);
	else if (sp->plus)
		ft_buffer(sp, "+", 1);
	else if (sp->space)
		ft_buffer(sp, " ", 1);
}

void	ft_rounding(t_sp *sp, char *p, char *ret)
{
	if (((*p != '.' && *(p + 1) >= '5') || (*p == '.' && *(p + 1) >= '5'))
		&& *(p + 1) != 'u')
	{
		while (p >= ret)
		{
			p = (*p == '.') ? p - 1 : p;
			if (p >= ret && *p < '9')
			{
				*p += 1;
				break ;
			}
			else if (p >= ret && *p == '9')
			{
				*p-- = '0';
				while (p >= ret && *p == '9')
					(*p-- != '.') ? *(p + 1) = '0' : 0;
				(p < ret) ? ft_buffer(sp, "1", 1) : 0;
				*p = (p >= ret) ? *p + 1 : *p;
				break ;
			}
			p--;
		}
	}
}

void	ft_format(t_sp *sp, char *ret, char *bin)
{
	char	*p;
	int		integral_size;

	if (ft_special_values(sp, ret))
		return ;
	p = ret;
	while (*p++ != '\0')
		*(p - 1) = (*(p - 1) == 'u') ? '0' : *(p - 1);
	sp->sign = (bin[0] == '1' || sp->plus || sp->space) ? 1 : 0;
	sp->precision = (sp->precision == -1) ? 6 : sp->precision;
	p = ret;
	integral_size = 0;
	while (*p++ != '.')
	{
		sp->output_size++;
		integral_size++;
	}
	ft_calc_format(sp, bin);
	ft_rounding(sp, ret + (integral_size + sp->precision), ret);
	ft_buffer(sp, ret, integral_size);
	if (sp->precision > 0 || sp->hash)
		ft_buffer(sp, ret + integral_size, sp->precision + 1);
	ft_print_right_spaces(sp);
}
