/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:47:45 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:35:04 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

void	ft_spaces_signed_base(t_sp *sp)
{
	sp->right_spaces = (sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size - sp->sign : 0;
	sp->left_spaces = (!sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size - sp->sign : 0;
}

void	ft_zeros_signed_base(t_sp *sp, long n, int base_size)
{
	sp->sign = (n < 0 || sp->plus || sp->space) ? 1 : 0;
	sp->output_size = (n == 0 && sp->precision != 0) ? 1 : sp->output_size;
	while (n != 0)
	{
		sp->output_size++;
		n /= base_size;
	}
	if (sp->precision != -1)
		sp->zeros = sp->precision - sp->output_size;
	else if (sp->left_align == 0 && sp->zero != 0)
		sp->zeros = sp->min_width - sp->output_size - sp->sign;
	if (sp->zeros < 0)
		sp->zeros = 0;
}

void	ft_print_signed(t_sp *sp, long n, char *base, int base_size)
{
	n = (n > 0) ? -n : n;
	if (n > (long)-base_size)
		ft_buffer(sp, &base[-n], 1);
	else
	{
		ft_print_signed(sp, n / base_size, base, base_size);
		ft_print_signed(sp, n % base_size, base, base_size);
	}
}

void	ft_signed(t_sp *sp)
{
	long	n;

	n = va_arg(sp->ap, long);
	n = (sp->type_size == 1) ? (char)n : n;
	n = (sp->type_size == 2) ? (short)n : n;
	n = (sp->type_size == 4) ? (int)n : n;
	ft_zeros_signed_base(sp, n, 10);
	ft_spaces_signed_base(sp);
	ft_print_left_spaces(sp);
	ft_print_sign(sp, n);
	ft_print_zeros(sp);
	if (n || sp->precision)
		ft_print_signed(sp, n, "0123456789", 10);
	ft_print_right_spaces(sp);
}

void	ft_print_base(t_sp *sp, char specifier)
{
	if (ft_strchr("dDiI", specifier))
		ft_signed(sp);
	else
		ft_unsigned(sp, specifier);
}
