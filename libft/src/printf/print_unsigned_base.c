/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:48:00 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:35:50 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

void	ft_spaces_base(t_sp *sp)
{
	sp->right_spaces = (sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size : 0;
	sp->left_spaces = (!sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size : 0;
}

void	ft_zeros_base(t_sp *sp, unsigned long n, int base_size)
{
	sp->output_size = (n == 0 && sp->precision != 0) ? 1 : sp->output_size;
	while (n != 0)
	{
		sp->output_size++;
		n /= base_size;
	}
	if (sp->precision != -1)
		sp->zeros = sp->precision - sp->output_size;
	else if (sp->left_align == 0 && sp->zero != 0)
		sp->zeros = sp->min_width - sp->output_size;
	if (sp->zeros < 0)
		sp->zeros = 0;
}

void	ft_print_unsigned(t_sp *sp, unsigned long n, char *base, int size)
{
	if (n < (unsigned long)size)
		ft_buffer(sp, &base[n], 1);
	else
	{
		ft_print_unsigned(sp, n / size, base, size);
		ft_print_unsigned(sp, n % size, base, size);
	}
}

void	ft_specs(char specifier, char **prefix, char **base, int *size)
{
	if (ft_strchr("b", specifier))
	{
		*prefix = "0b";
		*base = "01";
		*size = 2;
	}
	if (ft_strchr("oO", specifier))
	{
		*prefix = "0";
		*base = "01234567";
		*size = 8;
	}
	if (ft_strchr("uU", specifier))
	{
		*prefix = "";
		*base = "0123456789";
		*size = 10;
	}
	if (ft_strchr("xX", specifier))
	{
		*prefix = (specifier == 'x') ? "0x" : "0X";
		*base = (specifier == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
		*size = 16;
	}
}

void	ft_unsigned(t_sp *sp, char specifier)
{
	char			*prefix;
	char			*base;
	int				size;
	unsigned long	n;

	ft_specs(specifier, &prefix, &base, &size);
	n = va_arg(sp->ap, unsigned long);
	n = (sp->type_size == 1) ? (unsigned char)n : n;
	n = (sp->type_size == 2) ? (unsigned short)n : n;
	n = (sp->type_size == 4 && specifier != 'U' && specifier != 'O')
		? (unsigned int)n : n;
	sp->output_size = 0;
	if (n && sp->hash && sp->min_width != 0 && sp->precision == -1)
		sp->output_size += ft_strlen(prefix);
	ft_zeros_base(sp, n, size);
	if (n && sp->hash && (sp->min_width == 0 || sp->precision != -1))
		sp->output_size += ft_strlen(prefix);
	ft_spaces_base(sp);
	ft_print_left_spaces(sp);
	if (sp->hash && n)
		ft_buffer(sp, prefix, ft_strlen(prefix));
	ft_print_zeros(sp);
	if (n || sp->precision)
		ft_print_unsigned(sp, n, base, size);
	ft_print_right_spaces(sp);
}
