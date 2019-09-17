/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:00:31 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:13:01 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_address(t_sp *sp)
{
	unsigned long n;
	unsigned long tmp;

	n = va_arg(sp->ap, unsigned long);
	tmp = n;
	sp->output_size = (n == 0 && sp->precision != 0) ? 1 : 0;
	while (tmp != 0)
	{
		sp->output_size++;
		tmp /= 16;
	}
	(sp->precision != -1) ? sp->zeros = sp->precision - sp->output_size : 0;
	if (!sp->left_align && sp->zero)
		sp->zeros = sp->min_width - sp->output_size;
	(sp->zeros < 0) ? sp->zeros = 0 : 0;
	sp->right_spaces = (sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size - 2 : 0;
	sp->left_spaces = (!sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size - 2 : 0;
	ft_print_left_spaces(sp);
	ft_buffer(sp, "0x", 2);
	ft_print_zeros(sp);
	if (n != 0 || sp->precision != 0)
		ft_print_unsigned(sp, n, "0123456789abcdef", 16);
	ft_print_right_spaces(sp);
}
