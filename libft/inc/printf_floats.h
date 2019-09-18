/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_floats.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:33:53 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/18 09:35:46 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FLOATS_H
# define PRINTF_FLOATS_H

typedef struct	s_double_bits
{
	unsigned long long	mantissa:52;
	unsigned long long	exp:11;
	unsigned long long	sign:1;
}				t_double_bits;

typedef struct	s_ldouble_bits
{
	unsigned long long	mantissa:64;
	unsigned long long	exp:15;
	unsigned long long	sign:1;
	char				pad[6];
}				t_ldouble_bits;

typedef union	u_double
{
	double			dbl;
	t_double_bits	b;
	long double		ldbl;
	t_ldouble_bits	lb;
}				t_double;

char			*ft_strnewu(size_t size);
void			ft_strfree(char **s);
int				ft_bin2dec(char	*bin, int len);
void			ft_add_str(char *s1, char *s2);
void			ft_add_str_neg2power(char *neg2power, char *ret);
void			ft_calc(char *bin, int exp, char *ret);
void			ft_reverse(char *ret);
void			ft_format(t_sp *sp, char *ret, char *bin);
void			ft_add_pos2power(char *ret, int exp);
void			ft_add_neg2power(char *ret, int exp);
void			ft_double_str(char *s);
void			ft_sub_str(char *s1, char *s2);

#endif
