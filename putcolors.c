/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putcolors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 13:35:03 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 14:39:46 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static t_rgb	calc_delta(t_rgb a, t_rgb b)
{
	t_rgb	delt;

	delt.r = abs(a.r - b.r) * 100;
	delt.g = abs(a.g - b.g) * 100;
	delt.b = abs(a.b - b.b) * 100;
	return (delt);
}

static int		rgbtoi(t_rgb src)
{
	int		res;

	res = 0;
	res += src.b;
	res += src.g << 8;
	res += src.r << 16;
	return (res);
}

t_rgb			rgb_init(int color, int r, int g, int b)
{
	t_rgb	clr;

	clr.r = (color) ? ((color & 0xFF0000) >> 16) : r;
	clr.g = (color) ? ((color & 0xFF00) >> 8) : g;
	clr.b = (color) ? (color & 0xFF) : b;
	return (clr);
}

int				get_color_x(t_proj a, t_proj b, int curr)
{
	t_rgb	delt;
	int		koef;
	t_rgb	res;

	koef = 0;
	delt = calc_delta(a.color, b.color);
	koef = (curr - a.x) * 100 / (b.x - a.x);
	if (a.color.r >= b.color.r)
		res.r = ((a.color.r * 100) - ((delt.r * koef) / 100)) / 100;
	else
		res.r = ((a.color.r * 100) + ((delt.r * koef) / 100)) / 100;
	if (a.color.g >= b.color.g)
		res.g = ((a.color.g * 100) - ((delt.g * koef) / 100)) / 100;
	else
		res.g = ((a.color.g * 100) + ((delt.g * koef) / 100)) / 100;
	if (a.color.b >= b.color.b)
		res.b = ((a.color.b * 100) - ((delt.b * koef) / 100)) / 100;
	else
		res.b = ((a.color.b * 100) + ((delt.b * koef) / 100)) / 100;
	return (rgbtoi(res));
}

int				get_color_y(t_proj a, t_proj b, int curr)
{
	t_rgb	delt;
	int		koef;
	t_rgb	res;

	koef = 0;
	delt = calc_delta(a.color, b.color);
	koef = (curr - a.y) * 100 / (b.y - a.y);
	if (a.color.r >= b.color.r)
		res.r = ((a.color.r * 100) - ((delt.r * koef) / 100)) / 100;
	else
		res.r = ((a.color.r * 100) + ((delt.r * koef) / 100)) / 100;
	if (a.color.g >= b.color.g)
		res.g = ((a.color.g * 100) - ((delt.g * koef) / 100)) / 100;
	else
		res.g = ((a.color.g * 100) + ((delt.g * koef) / 100)) / 100;
	if (a.color.b >= b.color.b)
		res.b = ((a.color.b * 100) - ((delt.b * koef) / 100)) / 100;
	else
		res.b = ((a.color.b * 100) + ((delt.b * koef) / 100)) / 100;
	return (rgbtoi(res));
}
