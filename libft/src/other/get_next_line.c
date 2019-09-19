/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:04:47 by agelloz           #+#    #+#             */
/*   Updated: 2019/09/19 12:05:27 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		memmoveclear(void **dst, void *src)
{
	char		*d;
	char		*s;

	if (src == *dst)
		return ;
	d = (char*)*dst;
	s = (char*)src;
	while (*s)
		*d++ = *s++;
	while (*d)
		*d++ = '\0';
}

t_list		*delete_file(t_list **file, int fd)
{
	t_list *curr;
	t_list *prev;

	prev = NULL;
	curr = *file;
	if (curr->next)
		curr = curr->next;
	while (curr)
	{
		if ((int)curr->content_size == fd)
		{
			if (prev)
				prev->next = (curr->next == prev) ? NULL : curr->next;
			*file = (curr->next) ? curr->next : NULL;
			ft_memdel(&curr->content);
			free(curr);
			curr = NULL;
			return (*file);
		}
		prev = curr;
		curr = curr->next;
	}
	return (NULL);
}

t_list		*switch_file(t_list **file, int fd)
{
	t_list	*curr;
	t_list	*prev;
	int		stop;

	prev = NULL;
	curr = *file;
	stop = (curr) ? (int)curr->content_size : 0;
	while (curr)
	{
		if ((int)curr->content_size == fd)
			return (curr);
		prev = curr;
		curr = curr->next;
		if ((curr) && ((int)curr->content_size == stop))
			break ;
	}
	if (!(curr = malloc(sizeof(*curr)))
			|| !(curr->content = ft_strnew(0)))
		return (NULL);
	curr->content_size = fd;
	curr->next = (*file) ? *file : NULL;
	if (*file && prev)
		prev->next = curr;
	*file = curr;
	return (curr);
}

int			fill_line(t_list **file, char ***line, int fd)
{
	t_list	*c;
	char	*p;

	c = *file;
	if ((p = ft_strchr(c->content, '\n')))
	{
		**line = (p == c->content) ? ft_strnew(0) : ft_strsub(c->content,
					0, ft_strlen(c->content) - ft_strlen(p + 1) - 1);
		if (!(**line))
			return (-1);
		memmoveclear(&c->content, p + 1);
	}
	else
	{
		if (!(**line = ft_strdup(c->content)))
			return (-1);
		*file = delete_file(&(*file), fd);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*file;
	char			buf[BUFF_SIZE + 1];
	ssize_t			byt;

	ft_memset(buf, 0, BUFF_SIZE + 1);
	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0 || BUFF_SIZE <= 0)
			|| !(file = switch_file(&file, fd)))
		return (-1);
	if (ft_strchr(file->content, '\n'))
		return (fill_line(&file, &line, fd));
	while (!ft_strchr(file->content, '\n') && (byt = read(fd, buf, BUFF_SIZE)))
	{
		buf[byt] = '\0';
		if (!(file->content = ft_strjoin_free(file->content, buf)))
			return (-1);
	}
	if (byt < BUFF_SIZE && !ft_strlen(file->content))
	{
		file = delete_file(&file, fd);
		if (buf[0] == '\0')
			return (0);
		return ((*line = ft_strdup(buf)) ? 0 : -1);
	}
	return (fill_line(&file, &line, fd));
}
