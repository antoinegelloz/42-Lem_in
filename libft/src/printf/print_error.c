/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 20:11:41 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:14:39 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_error(t_sp *sp)
{
	if (sp->precision > 0)
		sp->zeros = sp->precision - 1;
	else if (!sp->left_align && sp->zero)
		sp->zeros = (sp->min_width - 1 >= 0) ? sp->min_width - 1 : 0;
	sp->right_spaces = (sp->left_align) ? sp->min_width - sp->zeros - 1 : 0;
	sp->left_spaces = (!sp->left_align) ? sp->min_width - sp->zeros - 1 : 0;
	ft_print_left_spaces(sp);
	ft_print_zeros(sp);
	if (*sp->error != '\0')
		ft_buffer(sp, sp->error, 1);
	ft_print_right_spaces(sp);
}
