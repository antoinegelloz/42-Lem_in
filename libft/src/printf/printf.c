/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 17:58:19 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 12:36:19 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

static void (*g_print_functions[128])(t_sp *sp) =
{
	['c'] = &ft_print_char,
	['s'] = &ft_print_string,
	['p'] = &ft_print_address,
	['o'] = &ft_print_octal,
	['O'] = &ft_print_octal,
	['f'] = &ft_print_float,
	['%'] = &ft_print_percent

};

void	ft_buffer(t_sp *sp, const char *format, int n)
{
	int	i;

	sp->ret = (sp->i + n > 2147483647) ? -1 : sp->ret;
	if (sp->i + n >= BUFF_SIZE_PRINTF)
	{
		write(sp->fd, sp->buffer, sp->i);
		sp->i = 0;
	}
	if (n < BUFF_SIZE_PRINTF)
	{
		i = 0;
		while (i < n)
		{
			sp->buffer[sp->i] = format[i];
			sp->i++;
			(sp->ret != -1) ? sp->ret++ : 0;
			i++;
		}
	}
	else
		write(sp->fd, format, n);
}

short	ft_parse_conversion(const char *format, int *i, t_sp *sp)
{
	while (ft_strchr("#-+ .0123456789hlL*", format[*i]))
	{
		if (ft_strchr("-+# 0", format[*i]))
			ft_parse_flags(format, i, sp);
		else if (ft_strchr("123456789*", format[*i]))
			ft_parse_width(format, i, sp);
		else if (format[*i] == '.')
			ft_parse_precision(format, i, sp);
		else if (ft_strchr("hlL", format[*i]))
			ft_parse_length_modifier(format, i, sp);
	}
	if (!ft_strchr("dDiIuUoOxXfFcCsSpb%", format[*i]))
	{
		sp->error = (char*)format + *i;
		if (format[*i] == '\0')
			(*i)--;
		return (0);
	}
	return ((short)format[*i]);
}

void	ft_parse_format(const char *format, t_sp *sp)
{
	int		i;
	short	specifier;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			specifier = ft_parse_conversion(format, &i, sp);
			if (ft_strchr("dDiIuUxXb", specifier))
				ft_print_base(sp, specifier);
			else if (g_print_functions[specifier] == NULL)
				ft_print_error(sp);
			else
				g_print_functions[specifier](sp);
		}
		else
			ft_buffer(sp, format + i, 1);
		ft_reset(sp);
		i++;
	}
}

int		ft_printf(const char *restrict format, ...)
{
	t_sp sp;

	if (!format)
		return (-1);
	ft_initialize(&sp, 1);
	va_start(sp.ap, format);
	ft_parse_format(format, &sp);
	write(1, sp.buffer, sp.i);
	va_end(sp.ap);
	return (sp.ret);
}

int		ft_fdprintf(int fd, const char *restrict format, ...)
{
	t_sp sp;

	if (!format)
		return (-1);
	ft_initialize(&sp, fd);
	va_start(sp.ap, format);
	ft_parse_format(format, &sp);
	write(fd, sp.buffer, sp.i);
	va_end(sp.ap);
	return (sp.ret);
}
