/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:23:16 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:05:22 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_initialize(t_sp *sp, int fd)
{
	int i;

	sp->i = 0;
	sp->ret = 0;
	sp->fd = fd;
	i = 0;
	while (i < BUFF_SIZE_PRINTF)
		sp->buffer[i++] = '\0';
	ft_reset(sp);
}

void	ft_reset(t_sp *sp)
{
	sp->error = "\0";
	sp->hash = 0;
	sp->zero = 0;
	sp->left_align = 0;
	sp->plus = 0;
	sp->space = 0;
	sp->min_width = 0;
	sp->precision = -1;
	sp->type_size = 4;
	sp->left_spaces = 0;
	sp->sign = 0;
	sp->zeros = 0;
	sp->output_size = 0;
	sp->right_spaces = 0;
}
