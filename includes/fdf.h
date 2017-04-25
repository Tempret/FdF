/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 18:42:02 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 17:42:41 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

# define PI			3.14159265358979323846264

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_coord
{
	double			x;
	double			y;
	double			z;
	t_rgb			color;
}					t_coord;

typedef struct		s_proj
{
	double			x;
	double			y;
	t_rgb			color;
}					t_proj;

typedef struct		s_win_param
{
	void			*mlx;
	void			*win;
	int				w_size;
	int				len;
	int				height;
	int				c_size;
	t_coord			**map;
	t_proj			**p_obj;
	int				web;
	int				info;
}					t_w_par;

typedef struct		s_rd_lst
{
	int				len;
	t_coord			*cd_arr;
	struct s_rd_lst	*next;
}					t_rd_lst;

t_rgb				rgb_init(int color, int r, int g, int b);
void				paint_map(t_proj **obj, t_w_par par);
void				paint_map(t_proj **obj, t_w_par par);
void				put_line(void *mlx, void *win, t_proj a, t_proj b);
int					get_color_x(t_proj a, t_proj b, int curr);
int					get_color_y(t_proj a, t_proj b, int curr);
t_rgb				rgb_init(int color, int r, int g, int b);
void				swap_coord(t_proj *a, t_proj *b);
void				swap_color(t_rgb *a, t_rgb *b);
void				put_web(void *mlx, void *win, int win_size);
void				put_info(t_w_par *w);
void				free_split(char **arr);
void				free_struct(t_w_par *p);
t_coord				**read_input_data(char *name, int *global_len,
	int *global_height, char **av);
int					atohex(char *str);
void				calc_cell_size(t_w_par *param);
void				projected_map(t_w_par *p);
t_proj				**new_proj(int len, int height);
int					fdf_key_hook(int keycode, void *param);
void				key_rotate(t_w_par *param, int keycode);
void				key_change_height(t_w_par *param, int key);
void				key_change_size(t_w_par *param, int keycode);
void				free_struct(t_w_par *p);

#endif
