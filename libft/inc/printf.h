/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:44:18 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/18 09:34:28 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# define BUFF_SIZE_PRINTF 18000

typedef struct	s_sp
{
	va_list	ap;
	int		fd;
	int		i;
	int		min_width;
	int		precision;
	int		left_spaces;
	int		sign;
	int		zeros;
	int		output_size;
	int		right_spaces;
	int		ret;
	char	buffer[BUFF_SIZE_PRINTF];
	char	*error;
	char	hash;
	char	zero;
	char	left_align;
	char	space;
	char	plus;
	char	type_size;
	char	pad[2];
}				t_sp;

int				ft_printf(const char *restrict format, ...);
int				ft_fdprintf(int fd, const char *restrict format, ...);
void			ft_initialize(t_sp *sp, int fd);
void			ft_reset(t_sp *sp);
void			ft_parse_flags(const char *format, int *i, t_sp *sp);
void			ft_parse_width(const char *format, int *i, t_sp *sp);
void			ft_parse_precision(const char *format, int *i, t_sp *sp);
void			ft_parse_length_modifier(const char *format, int *i, t_sp *sp);
void			ft_buffer(t_sp *sp, const char *format, int n);
void			ft_print_error(t_sp *sp);
void			ft_print_char(t_sp *sp);
void			ft_print_string(t_sp *sp);
void			ft_print_address(t_sp *sp);
void			ft_print_float(t_sp *sp);
void			ft_print_percent(t_sp *sp);
void			ft_signed(t_sp *sp);
void			ft_unsigned(t_sp *sp, char specifier);
void			ft_print_unsigned(t_sp *sp, unsigned long n, char *base,
									int base_size);
void			ft_print_base(t_sp *sp, char specifier);
void			ft_print_octal(t_sp *sp);
void			ft_zeros_base(t_sp *sp, unsigned long n, int base_size);
void			ft_spaces_base(t_sp *sp);
void			ft_print_left_spaces(t_sp *sp);
void			ft_print_sign(t_sp *sp, long n);
void			ft_print_zeros(t_sp *sp);
void			ft_print_right_spaces(t_sp *sp);

#endif
