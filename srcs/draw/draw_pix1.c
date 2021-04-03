/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pix1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:20:16 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/20 21:48:47 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	image_pixel_put(t_graf *graf, int x, int y, int color)
{
	int			point;

	if (x >= LEGENDA && x < graf->image.width && y >= 0 && \
		y < graf->image.height)
	{
		point = MAC_BPP * (x + y * graf->image.width);
		graf->image.addr[point] = color;
		graf->image.addr[++point] = color >> 8;
		graf->image.addr[++point] = color >> 16;
	}
}

void	put_line(t_point first, t_point second, t_graf *graf)
{
	t_bresen	bresen;
	t_point		current;

	ft_bzero(&bresen, sizeof(bresen));
	init_param(&first, &second, &bresen);
	current = first;
	while ((current.x - second.x) * bresen.sign_x <= 0 &&\
		(current.y - second.y) * bresen.sign_y <= 0)
	{
		image_pixel_put(graf, current.x, current.y,\
		color_gradient(&first, &current, &second));
		if (bresen.sum * 2 + bresen.dy >= 0)
		{
			bresen.sum = bresen.sum - bresen.dy;
			current.x = current.x + bresen.sign_x;
		}
		if (bresen.sum * 2 - bresen.dx <= 0)
		{
			bresen.sum = bresen.sum + bresen.dx;
			current.y = current.y + bresen.sign_y;
		}
	}
	image_pixel_put(graf, second.x, second.y,\
		color_gradient(&first, &current, &second));
}

t_point	define_point(int x, int y, t_graf *graf)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.p_color = graf->map.color[y][x];
	point.x = point.x * graf->scale;
	point.y = point.y * graf->scale;
	point.x = point.x + LEGENDA + (graf->width - LEGENDA -\
		graf->map.sym_count * graf->scale) / 2 + graf->scale / 2;
	point.y = point.y + (graf->height - graf->map.ln_count * graf->scale) / 2;
	return (point);
}

void	init_param(t_point *fst, t_point *scd, t_bresen *bresen)
{
	bresen->dx = abs(scd->x - fst->x);
	bresen->sign_x = (fst->x < scd->x) ? 1 : -1;
	bresen->dy = abs(scd->y - fst->y);
	bresen->sign_y = (fst->y < scd->y) ? 1 : -1;
	bresen->sum = bresen->dx - bresen->dy;
}
