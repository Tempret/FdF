/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 14:49:03 by dkhlopov          #+#    #+#             */
/*   Updated: 2017/01/22 15:18:06 by dkhlopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

t_proj	**new_proj(int len, int height)
{
	int		i;
	t_proj	**obj;

	i = 0;
	if (!(obj = (t_proj **)malloc(sizeof(t_proj *) * (height + 2))))
		return (NULL);
	while (i <= height)
	{
		if (!(obj[i] = (t_proj *)malloc(sizeof(t_proj) * (len + 1))))
			return (NULL);
		i++;
	}
	obj[i] = NULL;
	return (obj);
}

void	projected_map(t_w_par *p)
{
	int		i;
	int		j;

	i = 0;
	while (p->p_obj[i])
	{
		j = 0;
		while (j <= p->len)
		{
			p->p_obj[i][j].x = -p->map[i][j].x * cos(3 * PI / 4)
				- p->map[i][j].z * sin(3 * PI / 4) + 600;
			p->p_obj[i][j].y = p->map[i][j].x * sin(PI / 4) * cos(PI / 4) +
				p->map[i][j].y * cos(PI / 4) - p->map[i][j].z * sin(PI / 4) *
				cos(3 * PI / 4) + 600;
			p->p_obj[i][j].color = p->map[i][j].color;
			j++;
		}
		i++;
	}
}

void	calc_cell_size(t_w_par *param)
{
	param->w_size = 1200;
	param->c_size = (param->len > param->height) ? 600 / param->len :
		600 / param->height;
	if (param->c_size > 50)
		param->c_size = 50;
}

int		atohex(char *str)
{
	int		res;
	char	template[17];
	char	*end;

	ft_strcpy(template, "0123456789ABCDEF");
	res = 0;
	if (!(str = ft_strchr(str, 'x')))
		return (0);
	end = ++str;
	while (*end)
		end++;
	while (*str)
	{
		res += (ft_strchr(template, ft_toupper(*str)) - template)
			* pow(16, (end - str - 1));
		str++;
	}
	return (res);
}
