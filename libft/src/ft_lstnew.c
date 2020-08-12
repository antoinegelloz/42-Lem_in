/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:19:47 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/26 16:05:31 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne un maillon “frais”. Les champs content
** et content_size du nouveau maillon sont initialisés par copie des paramètres
** de la fonction. Si le paramètre content est nul, le champs content est
** initialisé à NULL et le champs content_size est initialisé à 0 quelque
** soit la valeur du paramètre content_size. Le champ next est initialisé
** à NULL. Si l’allocation échoue, la fonction renvoie NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	list->next = NULL;
	if (!content)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		if (!(list->content = malloc(content_size)))
		{
			free(list);
			list = NULL;
			return (NULL);
		}
		list->content_size = content_size;
		list->content = ft_memcpy(list->content, content, content_size);
	}
	return (list);
}
