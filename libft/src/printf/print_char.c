/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:33:01 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:13:49 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_char(t_sp *sp)
{
	char c;

	c = va_arg(sp->ap, int);
	if (!sp->left_align && sp->zero)
		sp->zeros = sp->min_width - 1;
	if (sp->left_align)
		sp->right_spaces = sp->min_width - sp->zeros - 1;
	else
		sp->left_spaces = sp->min_width - sp->zeros - 1;
	ft_print_left_spaces(sp);
	ft_print_zeros(sp);
	ft_buffer(sp, &c, 1);
	ft_print_right_spaces(sp);
}
