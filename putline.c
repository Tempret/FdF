/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 18:19:17 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 16:49:11 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void			paint_map(t_proj **obj, t_w_par par)
{
	int		i;
	int		j;

	i = 0;
	while (obj[i])
	{
		j = 0;
		while (j <= par.len)
		{
			if (j != par.len)
				put_line(par.mlx, par.win, obj[i][j], obj[i][j + 1]);
			if (i != par.height)
				put_line(par.mlx, par.win, obj[i][j], obj[i + 1][j]);
			j++;
		}
		i++;
	}
}

static void		put_line_x(void *mlx, void *win, t_proj a, t_proj b)
{
	double	y;
	double	x;
	int		color;

	if (a.x > b.x)
		swap_coord(&a, &b);
	x = a.x;
	y = a.y;
	while (x <= b.x)
	{
		color = get_color_x(a, b, x);
		mlx_pixel_put(mlx, win, x, y, color);
		x++;
		y = fabs((x - a.x) * (b.y - a.y) / (b.x - a.x));
		y = (a.y < b.y) ? (y + a.y) : (a.y - y);
	}
}

static void		put_line_y(void *mlx, void *win, t_proj a, t_proj b)
{
	double	y;
	double	x;
	int		swapped;
	int		color;

	swapped = 0;
	if (a.y > b.y)
	{
		swapped = 1;
		swap_coord(&a, &b);
	}
	x = a.x;
	y = a.y;
	while (y <= b.y)
	{
		color = get_color_y(a, b, y);
		mlx_pixel_put(mlx, win, x, y, color);
		y++;
		x = fabs((y - a.y) * (b.x - a.x) / (a.y - b.y));
		x = (a.x < b.x) ? (x + a.x) : (a.x - x);
	}
}

void			put_line(void *mlx, void *win, t_proj a, t_proj b)
{
	if (fabs(a.x - b.x) >= fabs(a.y - b.y))
		put_line_x(mlx, win, a, b);
	else
		put_line_y(mlx, win, a, b);
}
