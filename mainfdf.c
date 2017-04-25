/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainfdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:27:22 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/04/25 20:26:20 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void		set_size(t_w_par *par)
{
	int		i;
	int		j;
	float	center_x;
	float	center_z;

	i = 0;
	center_x = par->map[par->height][par->len].x / 2;
	center_z = par->map[par->height][par->len].z / 2;
	while (par->map[i])
	{
		j = 0;
		while (j <= par->len)
		{
			par->map[i][j].x = par->map[i][j].x *
				par->c_size - par->c_size * (center_x);
			par->map[i][j].y = par->map[i][j].y *
				par->c_size;
			par->map[i][j].z = par->map[i][j].z *
				par->c_size - par->c_size * (center_z);
			j++;
		}
		i++;
	}
}

void		put_info(t_w_par *w)
{
	mlx_string_put(w->mlx, w->win, 50, 970, 0xFFFFFF,
		"Hot keys:");
	mlx_string_put(w->mlx, w->win, 50, 990, 0xFFFFFF,
		"[a d] [w s] [q e] - rotate around axes [y][z][x]");
	mlx_string_put(w->mlx, w->win, 50, 1010, 0xFFFFFF,
		"[z x]             - change height");
	mlx_string_put(w->mlx, w->win, 50, 1030, 0xFFFFFF,
		"[+ -]             - zoom");
	mlx_string_put(w->mlx, w->win, 50, 1050, 0xFFFFFF,
		"    ^");
	mlx_string_put(w->mlx, w->win, 50, 1070, 0xFFFFFF,
		"[<- | ->]         - move figure");
	mlx_string_put(w->mlx, w->win, 50, 1090, 0xFFFFFF,
		"    v");
	mlx_string_put(w->mlx, w->win, 50, 1110, 0xFFFFFF,
		"[space]           - show coordinates (step 50 pxl)");
}

static int	general(t_w_par *w, char *name)
{
	w->web = 0;
	w->info = 0;
	calc_cell_size(w);
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, w->w_size,
			w->w_size, name);
	if (!w->mlx || !w->win)
		return (0);
	set_size(w);
	w->p_obj = new_proj(w->len, w->height);
	projected_map(w);
	paint_map(w->p_obj, *w);
	mlx_hook(w->win, 2, 0, fdf_key_hook, w);
	mlx_loop(w->mlx);
	return (1);
}

int			main(int argc, char **argv)
{
	t_w_par		w;

	w.map = NULL;
	if (argc == 2 && ft_strstr(argv[1], ".fdf"))
		w.map = read_input_data(argv[1], &w.len,
				&w.height, NULL);
	else if (argc == 6 && (!ft_strcmp(argv[2], "-color")))
		w.map = read_input_data(argv[1], &w.len,
				&w.height, argv);
	else
	{
		ft_putendl("usage: ./fdf source_file.fdf [-color R G B]");
		ft_putendl("       R, G, B - integer from 0 to 255");
		return (1);
	}
	if (!w.map || !(general(&w, argv[1])))
	{
		ft_putendl("File not found");
		return (1);
	}
	return (0);
}
