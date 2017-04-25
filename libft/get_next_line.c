/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 14:29:13 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/05 19:28:58 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_fd(t_file *begin, const int fd)
{
	t_file	*tmp;

	if (!begin)
		return (0);
	tmp = begin;
	while (tmp)
	{
		if (tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	return (!tmp) ? 0 : 1;
}

static char		*get_line(const int fd, t_file *begin)
{
	t_file	*dest;
	char	*line;
	char	*tmp;

	dest = begin;
	while (dest && dest->fd != fd)
		dest = dest->next;
	if (!(dest->content) || !*(dest->content))
		return (NULL);
	line = dest->content;
	if (!ft_strchr(dest->content, '\n'))
	{
		dest->content = NULL;
		return (line);
	}
	else
	{
		tmp = ft_strchr(dest->content, '\n');
		*tmp++ = '\0';
		dest->content = ft_strdup(tmp);
		return (line);
	}
}

static ssize_t	file_to_str(const int fd, char **line)
{
	ssize_t	nb;
	char	buff[BUFF_SIZE + 1];
	char	*file;
	char	*del;

	ft_bzero(buff, BUFF_SIZE + 1);
	nb = read(fd, buff, BUFF_SIZE);
	if (nb == -1 || nb == 0)
		return (nb);
	file = ft_strdup(buff);
	ft_bzero(buff, BUFF_SIZE + 1);
	while (read(fd, buff, BUFF_SIZE))
	{
		del = file;
		file = ft_strjoin(file, buff);
		if (del)
			free(del);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	*line = file;
	return (1);
}

static ssize_t	add_node(const int fd, t_file **begin)
{
	t_file	*new;
	char	*file;
	ssize_t nb;

	if (!(new = malloc(sizeof(t_file))))
		return (0);
	nb = file_to_str(fd, &file);
	if (nb == -1 || nb == 0)
		return (nb);
	new->content = file;
	new->fd = fd;
	if (!*begin)
	{
		*begin = new;
		new->next = NULL;
	}
	else
	{
		new->next = *begin;
		*begin = new;
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*begin;
	ssize_t			nb;

	if (!line)
		return (-1);
	if (check_fd(begin, fd) == 0)
	{
		nb = add_node(fd, &begin);
		if (nb == -1)
			return (-1);
	}
	*line = get_line(fd, begin);
	if (!*line)
		return (0);
	return (1);
}
