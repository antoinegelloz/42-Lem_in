/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:59:04 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/19 15:02:54 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i++])
	{
		if (s[i] == c || !s[i])
		{
			if (s[i - 1] != c)
				count++;
		}
	}
	return (count);
}

static void		free_table(char **tab, size_t master_i)
{
	while (--master_i)
	{
		free(tab[master_i]);
		tab[master_i] = NULL;
	}
}

static char		**ft_fill_table(char const *s, char **tab, char c)
{
	size_t	i;
	size_t	j;
	size_t	master_i;

	i = 0;
	j = 0;
	master_i = 0;
	while (s[i++])
	{
		if (s[i] == c || !s[i])
		{
			if (!(tab[master_i] = (char *)malloc(sizeof(char) * (i - j + 1))))
			{
				free_table(tab, master_i);
				return (NULL);
			}
			ft_strncpy(tab[master_i], s + j, i - j);
			tab[master_i++][i - j] = '\0';
			while (s[i] == c && s[i])
				i++;
			j = i;
		}
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char				**tab;
	size_t				count;
	size_t				i;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i] == c && s[i])
		i++;
	if (s[i])
		count = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	tab[count] = NULL;
	if (count)
	{
		if (!(tab = ft_fill_table(s + i, tab, c)))
		{
			free(tab);
			tab = NULL;
			return (NULL);
		}
	}
	return (tab);
}
