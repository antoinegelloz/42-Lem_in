/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_descending_order.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:14:00 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/05 14:15:35 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_descending_order(void *a, void *b)
{
	int elem1;
	int elem2;

	elem1 = *(int *)a;
	elem2 = *(int *)b;
	return (elem1 >= elem2);
}
