/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 18:55:25 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 16:49:57 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void	put_web(void *mlx, void *win, int win_size)
{
	int		web_x;
	int		web_y;

	web_x = 50;
	web_y = 50;
	while (web_y <= win_size)
	{
		web_x = 50;
		while (web_x <= win_size)
		{
			mlx_pixel_put(mlx, win, web_x, web_y, 0xFFFF00);
			web_x += 50;
		}
		web_y += 50;
	}
}

void	swap_color(t_rgb *a, t_rgb *b)
{
	int		tmp;

	tmp = a->r;
	a->r = b->r;
	b->r = tmp;
	tmp = a->g;
	a->g = b->g;
	b->g = tmp;
	tmp = a->b;
	a->b = b->b;
	b->b = tmp;
}

void	swap_coord(t_proj *a, t_proj *b)
{
	int		tmp;

	tmp = a->x;
	a->x = b->x;
	b->x = tmp;
	tmp = a->y;
	a->y = b->y;
	b->y = tmp;
	swap_color(&a->color, &b->color);
}

void	free_struct(t_w_par *p)
{
	int		i;

	i = 0;
	while (p->map[i])
		free(p->map[i++]);
	i = 0;
	while (p->p_obj[i])
		free(p->p_obj[i++]);
}

void	free_split(char **arr)
{
	int		i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free((char *)arr[i++]);
	free((char *)arr);
}
