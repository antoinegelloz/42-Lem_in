/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:03:50 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:18:19 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_percent(t_sp *sp)
{
	(!sp->left_align && sp->zero) ? sp->zeros = sp->min_width - 1 : 0;
	(sp->zeros < 0) ? sp->zeros = 0 : 0;
	sp->right_spaces = (sp->left_align) ? sp->min_width - sp->zeros - 1 : 0;
	sp->left_spaces = (!sp->left_align) ? sp->min_width - sp->zeros - 1 : 0;
	ft_print_left_spaces(sp);
	ft_print_zeros(sp);
	ft_buffer(sp, "%", 1);
	ft_print_right_spaces(sp);
}
