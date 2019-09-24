/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:48:00 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:17:26 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_octal(t_sp *sp)
{
	unsigned long	n;

	n = va_arg(sp->ap, unsigned long);
	n = (sp->type_size == 1) ? (unsigned char)n : n;
	n = (sp->type_size == 2) ? (unsigned short)n : n;
	n = (sp->type_size == 4) ? (unsigned int)n : n;
	sp->output_size = 0;
	ft_zeros_base(sp, n, 8);
	if (sp->hash && ((!sp->zeros && n) || (!sp->precision && !n)))
		sp->output_size += 1;
	ft_spaces_base(sp);
	ft_print_left_spaces(sp);
	if (sp->hash && ((!sp->zeros && n) || (!sp->precision && !n)))
		ft_buffer(sp, "0", 1);
	ft_print_zeros(sp);
	if (n || sp->precision)
		ft_print_unsigned(sp, n, "01234567", 8);
	ft_print_right_spaces(sp);
}
