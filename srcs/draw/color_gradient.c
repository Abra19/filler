/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_gradient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:19:13 by dlaure            #+#    #+#             */
/*   Updated: 2020/02/29 19:19:28 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

double	place(int start, int end, int current)
{
	double res;

	if (start == end)
		res = 1.0;
	else
		res = (current - start) * 1.0 / (end - start);
	return (res);
}

int		mix_light(int start, int end, double scale)
{
	int		mix;

	mix = (int)((1 - scale) * start + scale * end);
	return (mix);
}

int		color_gradient(t_point *start, t_point *current, t_point *end)
{
	double	scale;
	int		red;
	int		green;
	int		blue;

	if (start->p_color == end->p_color)
		return (start->p_color);
	if (abs(start->x - end->x) > abs(start->y - end->y))
		scale = place(start->x, end->x, current->x);
	else
		scale = place(start->y, end->y, current->y);
	red = mix_light((start->p_color >> 16) & 0xFF,\
	(end->p_color >> 16) & 0xFF, scale);
	green = mix_light((start->p_color >> 8) & 0xFF,\
	(end->p_color >> 8) & 0xFF, scale);
	blue = mix_light((start->p_color) & 0xFF,\
	(end->p_color) & 0xFF, scale);
	return ((red << 16 | green << 8 | blue));
}
