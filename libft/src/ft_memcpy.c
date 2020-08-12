/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:27:45 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/26 15:27:47 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memcpy() function copies n bytes from memory area src to memory area dst.
** If dst and src overlap, behavior is undefined. The memcpy() function
** returns the original value of dst.
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_cp;
	unsigned char	*src_cp;

	dst_cp = (unsigned char *)dst;
	src_cp = (unsigned char *)src;
	while (n-- > 0)
		*dst_cp++ = *src_cp++;
	return (dst);
}
