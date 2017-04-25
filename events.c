/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 15:47:52 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 17:37:48 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static void	move_map(t_coord **map, int x, int z, int len)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j <= len)
		{
			map[i][j].x = map[i][j].x + x;
			map[i][j].z = map[i][j].z + z;
			j++;
		}
		i++;
	}
}

static void	key_move(t_w_par *param, int keycode)
{
	if (keycode == 123)
		move_map(param->map, -20, 0, param->len);
	if (keycode == 124)
		move_map(param->map, 20, 0, param->len);
	if (keycode == 125)
		move_map(param->map, 0, 20, param->len);
	if (keycode == 126)
		move_map(param->map, 0, -20, param->len);
	mlx_clear_window(param->mlx, param->win);
	if (param->web)
		put_web(param->mlx, param->win, param->w_size);
	if (param->info)
		put_info(param);
	projected_map(param);
	paint_map(param->p_obj, *param);
}

static void	key_web(t_w_par *par)
{
	if (!par->web)
	{
		put_web(par->mlx, par->win, par->w_size);
		par->web = 1;
	}
	else
	{
		mlx_clear_window(par->mlx, par->win);
		if (par->info)
			put_info(par);
		paint_map(par->p_obj, *par);
		par->web = 0;
	}
}

static void	key_info(t_w_par *par)
{
	if (!par->info)
	{
		put_info(par);
		par->info = 1;
	}
	else
	{
		mlx_clear_window(par->mlx, par->win);
		if (par->web)
			put_web(par->mlx, par->win, par->w_size);
		paint_map(par->p_obj, *par);
		par->info = 0;
	}
}

int			fdf_key_hook(int keycode, void *param)
{
	t_w_par	*w;

	w = (t_w_par *)param;
	if (keycode == 53)
	{
		free_struct(w);
		exit(0);
	}
	if (keycode >= 123 && keycode <= 126)
		key_move(w, keycode);
	if (keycode == 49)
		key_web(w);
	if (keycode == 6 || keycode == 7)
		key_change_height(w, keycode);
	if (keycode == 78 || keycode == 69)
		key_change_size(w, keycode);
	if (keycode == 0 || keycode == 1 || keycode == 2 ||
			keycode == 12 || keycode == 13 || keycode == 14)
		key_rotate(w, keycode);
	if (keycode == 34)
		key_info(w);
	return (0);
}
