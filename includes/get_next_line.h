/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 18:53:52 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/13 16:15:57 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

# define BUFF_SIZE 4096

typedef struct		s_file
{
	char			*content;
	int				fd;
	struct s_file	*next;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
