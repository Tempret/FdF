/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 13:25:22 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 16:46:59 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static void	reduce_map(t_w_par *param)
{
	int		i;
	int		j;

	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (j <= param->len)
		{
			param->map[i][j].x = param->map[i][j].x * 0.8;
			param->map[i][j].y = param->map[i][j].y * 0.8;
			param->map[i][j].z = param->map[i][j].z * 0.8;
			j++;
		}
		i++;
	}
}

static void	increase_map(t_w_par *param)
{
	int		i;
	int		j;

	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (j <= param->len)
		{
			param->map[i][j].x = param->map[i][j].x * 1.2;
			param->map[i][j].y = param->map[i][j].y * 1.2;
			param->map[i][j].z = param->map[i][j].z * 1.2;
			j++;
		}
		i++;
	}
}

void		key_change_height(t_w_par *param, int key)
{
	int		i;
	int		j;

	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (j <= param->len)
		{
			if (key == 6)
				param->map[i][j].y = param->map[i][j].y * 1.2;
			else
				param->map[i][j].y = param->map[i][j].y * 0.8;
			j++;
		}
		i++;
	}
	mlx_clear_window(param->mlx, param->win);
	if (param->web)
		put_web(param->mlx, param->win, param->w_size);
	if (param->info)
		put_info(param);
	projected_map(param);
	paint_map(param->p_obj, *param);
}

void		key_change_size(t_w_par *param, int keycode)
{
	if (keycode == 78)
		reduce_map(param);
	if (keycode == 69)
		increase_map(param);
	mlx_clear_window(param->mlx, param->win);
	if (param->web)
		put_web(param->mlx, param->win, param->w_size);
	if (param->info)
		put_info(param);
	projected_map(param);
	paint_map(param->p_obj, *param);
}
