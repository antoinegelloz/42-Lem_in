/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:58:56 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:35:25 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_strlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_print_string(t_sp *sp)
{
	char *str;

	str = va_arg(sp->ap, char *);
	str = (str == NULL) ? "(null)" : str;
	sp->output_size = (sp->precision != 0) ? ft_strlen(str) : 0;
	sp->output_size = (sp->precision > 0 && sp->precision < sp->output_size)
		? sp->precision : sp->output_size;
	sp->zeros = (!sp->left_align && sp->zero) ? sp->min_width
		- sp->output_size : 0;
	sp->right_spaces = (sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size : 0;
	sp->left_spaces = (!sp->left_align) ? sp->min_width - sp->zeros
		- sp->output_size : 0;
	ft_print_left_spaces(sp);
	ft_print_zeros(sp);
	ft_buffer(sp, str, sp->output_size);
	ft_print_right_spaces(sp);
}
