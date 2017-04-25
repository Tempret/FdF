/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 13:20:18 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 17:36:50 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static void	rotate_y(t_w_par *param, int dir)
{
	int		i;
	int		j;
	float	x;
	float	z;

	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (j <= param->len)
		{
			x = param->map[i][j].x;
			z = param->map[i][j].z;
			param->map[i][j].x = (dir > 0) ?
				x * cos(PI / 12.0) + z * sin(PI / 12.0) :
				x * cos(PI / 12.0) - z * sin(PI / 12.0);
			param->map[i][j].z = (dir > 0) ?
				-x * sin(PI / 12.0) + z * cos(PI / 12.0) :
				x * sin(PI / 12.0) + z * cos(PI / 12.0);
			j++;
		}
		i++;
	}
}

static void	rotate_x(t_w_par *param, int dir)
{
	int		i;
	int		j;
	float	y;
	float	z;

	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (j <= param->len)
		{
			y = param->map[i][j].y;
			z = param->map[i][j].z;
			param->map[i][j].y = (dir > 0) ?
				y * cos(PI / 12.0) - z * sin(PI / 12.0) :
				y * cos(PI / 12.0) + z * sin(PI / 12.0);
			param->map[i][j].z = (dir > 0) ?
				y * sin(PI / 12.0) + z * cos(PI / 12.0) :
				-y * sin(PI / 12.0) + z * cos(PI / 12.0);
			j++;
		}
		i++;
	}
}

static void	rotate_z(t_w_par *param, int dir)
{
	int		i;
	int		j;
	float	x;
	float	y;

	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (j <= param->len)
		{
			x = param->map[i][j].x;
			y = param->map[i][j].y;
			param->map[i][j].x = (dir > 0) ?
				x * cos(PI / 12.0) - y * sin(PI / 12.0) :
				x * cos(PI / 12.0) + y * sin(PI / 12.0);
			param->map[i][j].y = (dir > 0) ?
				x * sin(PI / 12.0) + y * cos(PI / 12.0) :
				-x * sin(PI / 12.0) + y * cos(PI / 12.0);
			j++;
		}
		i++;
	}
}

void		key_rotate(t_w_par *param, int keycode)
{
	if (keycode == 0)
		rotate_y(param, -1);
	if (keycode == 2)
		rotate_y(param, 1);
	if (keycode == 13)
		rotate_x(param, -1);
	if (keycode == 1)
		rotate_x(param, 1);
	if (keycode == 12)
		rotate_z(param, -1);
	if (keycode == 14)
		rotate_z(param, 1);
	mlx_clear_window(param->mlx, param->win);
	if (param->web)
		put_web(param->mlx, param->win, param->w_size);
	if (param->info)
		put_info(param);
	projected_map(param);
	paint_map(param->p_obj, *param);
}
