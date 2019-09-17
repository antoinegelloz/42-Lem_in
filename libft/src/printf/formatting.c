/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:51:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:07:00 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_left_spaces(t_sp *sp)
{
	while (sp->left_spaces-- > 0)
		ft_buffer(sp, " ", 1);
}

void	ft_print_sign(t_sp *sp, long n)
{
	if (sp->sign)
	{
		if (n < 0)
			ft_buffer(sp, "-", 1);
		else if (sp->plus)
			ft_buffer(sp, "+", 1);
		else if (sp->space)
			ft_buffer(sp, " ", 1);
	}
}

void	ft_print_zeros(t_sp *sp)
{
	while (sp->zeros-- > 0)
		ft_buffer(sp, "0", 1);
}

void	ft_print_right_spaces(t_sp *sp)
{
	while (sp->right_spaces-- > 0)
		ft_buffer(sp, " ", 1);
}
