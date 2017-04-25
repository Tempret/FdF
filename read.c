/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 12:58:14 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 18:46:59 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static t_coord	*str_to_coord(char **arr, int len, int num, char **av)
{
	int		i;
	t_coord	*coord_arr;

	i = 0;
	if (!len)
		return (NULL);
	if (!(coord_arr = malloc(sizeof(t_coord) * len)))
		return (NULL);
	while (i < len)
	{
		coord_arr[i].x = i;
		coord_arr[i].y = -ft_atoi(arr[i]);
		coord_arr[i].z = num;
		if (!av)
			coord_arr[i].color = rgb_init(atohex(arr[i]), 255, 255, 255);
		else
			coord_arr[i].color = rgb_init(atohex(arr[i]), ft_atoi(av[2]),
				ft_atoi(av[3]), ft_atoi(av[4]));
		i++;
	}
	return (coord_arr);
}

static int		calc_len(char **arr)
{
	int		count;

	count = 0;
	if (!arr)
		return (0);
	while (arr[count])
		count++;
	return (count);
}

static int		add_elem(t_rd_lst **begin, char *line, char **av)
{
	t_rd_lst	*tmp;
	t_rd_lst	*new;
	char		**split;
	static int	num = 0;

	if (!(new = malloc(sizeof(t_rd_lst))))
		return (0);
	split = ft_strsplit(line, ' ');
	free(line);
	new->len = calc_len(split);
	new->cd_arr = str_to_coord(split, new->len, num, av);
	free_split(split);
	new->next = NULL;
	if (!*begin)
		*begin = new;
	else
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	num++;
	return (num);
}

static t_coord	**mapassembl(t_rd_lst *begin, int height)
{
	t_coord	**map;
	int		i;

	i = 0;
	if (!(map = (t_coord **)malloc(sizeof(t_coord *) * (height + 1))))
		return (NULL);
	while (i < height)
	{
		map[i++] = begin->cd_arr;
		begin = begin->next;
	}
	map[i] = NULL;
	return (map);
}

t_coord			**read_input_data(char *name, int *global_len,
		int *global_height, char **av)
{
	int			fd[2];
	char		*line;
	t_coord		**map;
	t_rd_lst	*begin;
	int			height;

	begin = NULL;
	fd[0] = open(name, O_RDONLY);
	while ((fd[1] = get_next_line(fd[0], &line)))
	{
		if (fd[1] == -1)
			return (NULL);
		height = add_elem(&begin, line, av);
	}
	map = mapassembl(begin, height);
	*global_len = begin->len - 1;
	*global_height = height - 1;
	close(fd[0]);
	return (map);
}
