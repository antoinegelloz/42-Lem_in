/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:05 by agelloz           #+#    #+#             */
/*   Updated: 2019/05/27 10:19:52 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne un tableau de chaînes de
** caractères “fraiches” (toutes terminées par un ’\0’, le tableau
** également donc) résultant de la découpe de s selon le caractère
** c. Si l’allocation echoue, la fonction retourne NULL. Exemple :
** ft_strsplit("*salut*les***etudiants*", ’*’) renvoie
** le tableau ["salut", "les", "etudiants"].
*/

#include "libft.h"

static size_t	ft_nb_wds(const char *s, size_t i, char c)
{
	size_t nb_wds;

	if (!s)
		return (0);
	nb_wds = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nb_wds += 1;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb_wds);
}

static size_t	ft_nb_char(const char *s, size_t i, char c)
{
	size_t nb_char;

	nb_char = 0;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (nb_char);
	while (s[i] && s[i] != c)
	{
		nb_char += 1;
		i++;
	}
	return (nb_char);
}

static char		**ft_fill_in_tab(const char *s, size_t *i, size_t nb_char,
		char **tab)
{
	size_t j;
	size_t wd;

	wd = 0;
	while (tab[wd][0])
		wd++;
	j = 0;
	while (j < nb_char)
	{
		tab[wd][j] = s[*i];
		*i += 1;
		j++;
	}
	tab[wd][j] = '\0';
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		wd;
	size_t		nb_char;
	size_t		nb_wds;

	i = 0;
	nb_wds = ft_nb_wds(s, i, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_wds + 1))))
		return (NULL);
	wd = 0;
	while (wd < nb_wds)
	{
		while (s[i] && (s[i] == c))
			i++;
		if (!s[i])
			return (tab);
		nb_char = ft_nb_char(s, i, c);
		if (!(tab[wd] = ft_strnew(nb_char)))
			return (NULL);
		tab = ft_fill_in_tab(s, &i, nb_char, tab);
		wd += 1;
	}
	tab[wd] = NULL;
	return (tab);
}
