/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:26:58 by agelloz           #+#    #+#             */
/*   Updated: 2019/04/24 15:41:32 by agelloz          ###   ########.fr       */
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
	t_list	*new_link;

	if (!(new_link = malloc(sizeof(*new_link))))
		return (NULL);
	if (content == NULL)
	{
		new_link->content = NULL;
		new_link->content_size = 0;
	}
	else
	{
		new_link->content = (void*)malloc(sizeof(size_t) * content_size);
		if (!(new_link->content))
		{
			free(new_link);
			return (NULL);
		}
		ft_memcpy(new_link->content, content, content_size);
		new_link->content_size = content_size;
	}
	new_link->next = NULL;
	return (new_link);
}
