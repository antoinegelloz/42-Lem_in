/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:10:18 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/16 15:24:27 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

void	ft_parse_flags(const char *format, int *i, t_sp *sp)
{
	while (ft_strchr("-+# 0", format[*i]))
	{
		if (format[*i] == '-')
			sp->left_align = 1;
		else if (format[*i] == '+')
			sp->plus = 1;
		else if (format[*i] == ' ')
			sp->space = 1;
		else if (format[*i] == '#')
			sp->hash = 1;
		else if (format[*i] == '0')
			sp->zero = 1;
		(*i)++;
	}
}

void	ft_parse_width(const char *format, int *i, t_sp *sp)
{
	int	min_width;

	if (format[*i] >= '1' && format[*i] <= '9')
	{
		min_width = ft_atoi(format + *i);
		sp->min_width = min_width;
		while (format[*i] >= '0' && format[*i] <= '9')
			(*i)++;
	}
	else if (format[*i] == '*')
	{
		sp->min_width = va_arg(sp->ap, int);
		if (sp->min_width < 0)
		{
			sp->left_align = 1;
			sp->min_width = -sp->min_width;
		}
		(*i)++;
	}
}

void	ft_parse_precision(const char *format, int *i, t_sp *sp)
{
	while (format[*i] == '.')
		(*i)++;
	if (format[*i] >= '0' && format[*i] <= '9')
	{
		sp->precision = ft_atoi(format + *i);
		while (format[*i] >= '0' && format[*i] <= '9')
			(*i)++;
	}
	else if (format[*i] == '*')
	{
		sp->precision = va_arg(sp->ap, int);
		sp->precision = (sp->precision < 0) ? -1 : sp->precision;
		(*i)++;
	}
	else
		sp->precision = 0;
}

void	ft_parse_length_modifier(const char *format, int *i, t_sp *sp)
{
	int	l;
	int	h;
	int	ld;

	l = 0;
	h = 0;
	ld = 0;
	while (ft_strchr("lhL", format[*i]))
	{
		l += (format[*i] == 'l') ? 1 : 0;
		h += (format[*i] == 'h') ? 1 : 0;
		ld += (format[*i] == 'L') ? 1 : 0;
		(*i)++;
	}
	if (l == 0 && h == 0)
		sp->type_size = 4;
	else if (l >= 1)
		sp->type_size = 8;
	else if (h == 1)
		sp->type_size = 2;
	else if (h == 2)
		sp->type_size = 1;
	if (ld >= 1)
		sp->type_size = 8;
}
